#include "funcoes.h"

int main(int argc, char *argv[]) {
    // Variáveis de configuração do sistema
    int tamanhoMemoriaReal, tamanhoMemoriaVirtual, processos, tamanhoPaginasProcesso, paginaInicialReal, paginaInicialVirtual;
    int execucao[TAM_VET];

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
    printf("Processos: %d, Páginas por Processo: %d\n", processos, tamanhoPaginasProcesso);
    printf("Página Inicial Real: %d, Página Inicial Virtual: %d\n", paginaInicialReal, paginaInicialVirtual);

    printf("\nOrdem de Execução:\n");
    for (int i = 0; execucao[i] != -1; i += 2) {
        printf("Processo %d, Página %d\n", execucao[i], execucao[i + 1]);
    }

    for (int i = 0; execucao[i] != -1; i += 2) {
        int processoId = execucao[i];
        int paginaVirtual = execucao[i + 1];
    
        int enderecoFisico = gerenciarPagina(processoId, paginaVirtual);
        if (enderecoFisico == -1) {
            // Falta de página
            lidarComFaltaDePaginaFIFO(processoId, paginaVirtual);
        } else {
            printf("Acesso à memória: Processo %d, Página Virtual %d, Frame %d\n", processoId, paginaVirtual, enderecoFisico);
            registrarLog("Acesso à Memória", processoId, paginaVirtual, enderecoFisico);
        }
    }

    return 0;
}
