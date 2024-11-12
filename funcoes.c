// Arquivo funcoes.c
#include "funcoes.h"
#include <string.h>  // Para funções de string

Pagina tabelaDePaginas[TAM_VET];

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
