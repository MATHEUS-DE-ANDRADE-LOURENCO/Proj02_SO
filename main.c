#include "funcoes.h"

int main(int argc, char *argv[]) {
    // Variáveis de configuração do sistema
    int tamanhoMemoriaReal, tamanhoMemoriaVirtual, processos, tamanhoPaginasProcesso, paginaInicialReal, paginaInicialVirtual;
    int execucao[TAM_VET];

    for(int i = 0; i < TAM_VET; i++) execucao[i] = -1;

    // Inicialização do sistema com dados do arquivo params.csv
    if (!inicializarSistema(&tamanhoMemoriaReal, &tamanhoMemoriaVirtual, &processos, &tamanhoPaginasProcesso, 
                            &paginaInicialReal, &paginaInicialVirtual, "params.csv")) {
        printf("Erro ao ler o arquivo de parâmetros.\n");
        return 1;
    }

    // Carrega a ordem de execução de execucao.csv no vetor execucao
    if (!carregarOrdemExecucao(execucao, "execucao.csv")) {
        printf("Erro ao ler o arquivo de execução.\n");
        return 1;
    }

    // Exibir os valores lidos para verificação
    printf("Configurações do Sistema:\n");
    printf("Memória Real: %d, Memória Virtual: %d\n", tamanhoMemoriaReal, tamanhoMemoriaVirtual);
    printf("Processos: %d, Tamanho de cada página: %d\n", processos, tamanhoPaginasProcesso);
    printf("Página Inicial Real: %d, Página Inicial Virtual: %d\n", paginaInicialReal, paginaInicialVirtual);

    printf("\nOrdem de Execução:\n");
    for (int i = 0; execucao[i] != -1; i += 2) {
        printf("Processo %d, Página %d\n", execucao[i], execucao[i + 1]);
    }

    // Inicializa a memória virtual
    Processo memVirtual[TAM_VET];

    for (int i = 0; i < TAM_VET; i++) {
        memVirtual[i].pid = -1;
    }

    Processo procAux;
    int posMemoriaVirtual = 0;

    // Percorrer o vetor de execução analisando os processos
    for (int i = 0; execucao[i] != -1; i += 2) {
        // Se o processo com esse PID não estiver na memória:
        if (!jaEstaNaMemoriaVirtual(execucao[i], memVirtual)) {
            // Inicializar um processo com esse ID
            procAux.pid = execucao[i];
            procAux.enderecoVirtual = paginaInicialVirtual;

            int posPagina = 0;
            int endPagina = paginaInicialVirtual;
            // Alocando as páginas ao processo
            for(int j = 0; j < tamanhoPaginasProcesso; j++) {
                Pagina pagAux;
                pagAux.id = j + 1;
                pagAux.paginaVirtual = endPagina;
                pagAux.estaNaMemoria = 0;
                pagAux.processoId = execucao[i];

                procAux.paginas[posPagina] = pagAux;
                posPagina++;
                endPagina+=4;
            }

            // Armazena o processo na memória virtual
            memVirtual[posMemoriaVirtual] = procAux;
            posMemoriaVirtual++;  // Incrementa a posição de memória virtual
            paginaInicialVirtual += 4 * tamanhoPaginasProcesso;
        }
    }

    // Imprime a memória virtual
    imprimeMemoriaVirtual(memVirtual, tamanhoPaginasProcesso, posMemoriaVirtual);

    return 0;
}
