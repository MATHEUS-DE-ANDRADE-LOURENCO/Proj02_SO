// Arquivo funcoes.c
#include "funcoes.h"
#include <string.h>  // Para funções de string

Pagina tabelaDePaginas[TAM_VET];

// Variável para armazenar a fila FIFO de substituição
int fifoQueue[TAM_VET];
int fifoFront = 0;
int fifoRear = -1;
int totalFrames = 0;  // Total de frames ocupados

int posicaoPontoVirgula(const char *linha) {
    char *pontoVirgula = strchr(linha, ';');
    if (pontoVirgula != NULL) {
        return pontoVirgula - linha;  // Retorna o índice do ponto e vírgula
    }
    return -1;  // Retorna -1 se não encontrar
}

int inicializarSistema(int *tamanhoMemoriaReal, int *tamanhoMemoriaVirtual, int *processos, 
                       int *tamanhoPaginasProcesso, int *paginaInicialReal, int *paginaInicialVirtual, 
                       const char *arquivoParams) {
    FILE *params = fopen(arquivoParams, "r");
    if (params == NULL) {
        printf("Erro ao abrir o arquivo de parâmetros.\n");
        return 0;
    }

    char linha[TAM_VET];
    int valor;

    // Lê cada linha do arquivo params.csv
    while (fgets(linha, TAM_VET, params)) {
        // Encontra o índice do ponto e vírgula
        int pos = posicaoPontoVirgula(linha);
        if (pos == -1) {
            printf("Formato inválido em uma linha do arquivo de parâmetros.\n");
            fclose(params);
            return 0;
        }

        // Extrai o valor após o ponto e vírgula
        valor = atoi(&linha[pos + 1]);

        // Verifica o conteúdo da linha e atribui o valor correto
        if (strstr(linha, "Memória Real")) *tamanhoMemoriaReal = valor;
        else if (strstr(linha, "Memória Virtual")) *tamanhoMemoriaVirtual = valor;
        else if (strstr(linha, "Processos")) *processos = valor;
        else if (strstr(linha, "Tamanho Páginas Processo")) *tamanhoPaginasProcesso = valor;
        else if (strstr(linha, "Página Inicial Real")) *paginaInicialReal = valor;
        else if (strstr(linha, "Página Inicial Virtual")) *paginaInicialVirtual = valor;
        else {
            printf("Parâmetro desconhecido no arquivo de parâmetros: %s\n", linha);
        }
    }

    fclose(params);
    return 1;
}

void inicializarTabelaDePaginas() {
    for (int i = 0; i < TAM_VET; i++) {
        tabelaDePaginas[i].processoId = -1;
        tabelaDePaginas[i].paginaVirtual = -1;
        tabelaDePaginas[i].paginaReal = -1;
        tabelaDePaginas[i].estaNaMemoria = 0;
    }
}

int gerenciarPagina(int processoId, int paginaVirtual) {
    for (int i = 0; i < TAM_VET; i++) {
        if (tabelaDePaginas[i].processoId == processoId && tabelaDePaginas[i].paginaVirtual == paginaVirtual) {
            return tabelaDePaginas[i].estaNaMemoria ? tabelaDePaginas[i].paginaReal : -1;
        }
    }
    return -1;
}

int carregarOrdemExecucao(int execucao[TAM_VET], const char *arquivoExecucao) {
    FILE *exec;
    char linha[TAM_VET];
    int i = 0;
    int posPontoVirgula;

    exec = fopen(arquivoExecucao, "r");
    if (exec == NULL) return 0;

    while (fgets(linha, TAM_VET, exec) && i < TAM_VET - 1) {
        posPontoVirgula = posicaoPontoVirgula(linha);
        execucao[i] = atoi(&linha[0]);
        execucao[i + 1] = atoi(&linha[posPontoVirgula + 1]);
        i += 2;
    }
    execucao[i] = -1; // Marca o fim da lista de execuções
    fclose(exec);
    return 1;
}

// Função para adicionar uma página ao final da fila FIFO
void adicionarFilaFIFO(int frameIndex) {
    fifoRear = (fifoRear + 1) % TAM_VET;
    fifoQueue[fifoRear] = frameIndex;
}

// Função para remover a página mais antiga da fila FIFO
int removerFilaFIFO() {
    int frameIndex = fifoQueue[fifoFront];
    fifoFront = (fifoFront + 1) % TAM_VET;
    return frameIndex;
}


int encontrarFrameLivre() {
    for (int i = 0; i < TAM_VET; i++) {
        if (tabelaDePaginas[i].estaNaMemoria == 0) {
            return i;  // Retorna o índice do primeiro frame livre
        }
    }
    return -1;  // Nenhum frame livre encontrado
}

void lidarComFaltaDePaginaFIFO(int processoId, int paginaVirtual) {
    printf("Falta de Pagina\n");
    sleep(1);  // Simula o tempo de acesso à memória secundária
    
    int frameIndex = encontrarFrameLivre();
    
    if (frameIndex == -1) {
        // Memória cheia, então remover a página mais antiga (FIFO)
        frameIndex = removerFilaFIFO();
        registrarLog("Substituição de Página (FIFO)", tabelaDePaginas[frameIndex].processoId,
                     tabelaDePaginas[frameIndex].paginaVirtual, frameIndex);
        tabelaDePaginas[frameIndex].processoId = processoId;
        tabelaDePaginas[frameIndex].paginaVirtual = paginaVirtual;
    } else {
        // Frame livre encontrado
        tabelaDePaginas[frameIndex].processoId = processoId;
        tabelaDePaginas[frameIndex].paginaVirtual = paginaVirtual;
        adicionarFilaFIFO(frameIndex);
    }
    
    tabelaDePaginas[frameIndex].estaNaMemoria = 1;
    registrarLog("Página carregada", processoId, paginaVirtual, frameIndex);
}


void registrarLog(const char *mensagem, int processoId, int paginaVirtual, int paginaReal) {
    FILE *log = fopen("log_execucao.txt", "a");
    if (log != NULL) {
        fprintf(log, "Processo %d, Página Virtual %d, Página Real %d: %s\n", processoId, paginaVirtual, paginaReal, mensagem);
        fclose(log);
    } else {
        printf("Erro ao abrir o arquivo de log.\n");
    }
}


bool jaEstaNaMemoriaVirtual(int pid, Processo memoriaVirtual[TAM_VET]) {
    for(int i = 0; i < TAM_VET; i = i + 2) {
        if(memoriaVirtual[i].pid == pid) return true;
    }

    return false;
}

void imprimeMemoriaVirtual(Processo memoriaVirtual[TAM_VET], int tamanhoPaginasProcesso, int qtdProcessos) {
    printf("\n--------------- --------------- ---------------");
    printf("\n|             |               |               |");
    printf("\n--------------- --------------- ---------------");

    for (int i = 0; i < qtdProcessos; i++) {
        printf("\n--------------- --------------- ---------------");
        printf("\n|");

        // Imprime as páginas do processo atual
        for (int j = 0; j < tamanhoPaginasProcesso; j++) {
            printf(" P%d -%d- %d  |", 
                   memoriaVirtual[i].pid, 
                   memoriaVirtual[i].paginas[j].id, 
                   memoriaVirtual[i].paginas[j].paginaVirtual);
        }
    }
    printf("\n--------------- --------------- ---------------\n");
}
