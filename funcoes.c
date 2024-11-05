# include "funcoes.h"

int posicaoPontoVirgula(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ';') {
            return i;
        }
    }
    return -1; // Caso não haja ponto e vírgula
}

bool inicializarSistema(int *tamanhoMemoriaReal, int *tamanhoMemoriaVirtual, int *processos, int *tamanhoPaginasProcesso, int *paginaInicialReal, int *paginaInicialVirtual, int execucao[TAM_VET], char *parametros, char *ordemExecucao) {
    FILE *params = fopen(parametros, "r");
    FILE *exec = fopen(ordemExecucao, "r");

    if(params == NULL || exec == NULL) {
        printf("\nErro na abertura dos arquivos.");
        return false;
    }

    char *linha;
    linha = (char*) calloc(TAM_VET, sizeof(char));

    fgets(linha, TAM_VET, params);
    *tamanhoMemoriaReal = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    *tamanhoMemoriaVirtual= linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    *processos = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    *tamanhoPaginasProcesso = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    *paginaInicialReal = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    *paginaInicialVirtual= linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fclose(params);
    fclose(exec);
    free(linha);

    return true;
}