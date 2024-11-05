#include "funcoes.h"

int main(int argc, char *argv[]) {  // Corrigido aqui

    int tamanhoMemoriaReal, tamanhoMemoriaVirtual, processos, tamanhoPaginasProcesso, paginaInicialReal, paginaInicialVirtual;
    int execucao[TAM_VET];
    // ============================================== LER OS ARQUIVOS E PREPARAR AS VARIÁVEIS ==============================================

    // Abrir arquivos
    FILE *params = fopen(argv[1], "r");
    FILE *exec = fopen(argv[2], "r");  // Aqui, talvez você queria abrir o segundo arquivo

    if(params == NULL || exec == NULL) {
        printf("\nErro na abertura dos arquivos.");
        return 1; // Usar 1 para indicar erro
    }

    char *linha;
    linha = (char*) calloc(TAM_VET, sizeof(char));

    // Leitura dos dados do arquivo params
    fgets(linha, TAM_VET, params);
    tamanhoMemoriaReal = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    tamanhoMemoriaVirtual= linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    processos = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    tamanhoPaginasProcesso = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    paginaInicialReal = linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    fgets(linha, TAM_VET, params);
    paginaInicialVirtual= linha[posicaoPontoVirgula(linha) + 1] - '0'; 

    printf("%d %d %d %d", tamanhoMemoriaReal, tamanhoMemoriaReal, processos, tamanhoPaginasProcesso);

    for(int i = 0; fgets(linha, TAM_VET, exec) != NULL; i + 2) {
        execucao[i] = linha[0] - '0';
        execucao[i + 1] = linha[2] - '0';

        printf("\n%d %d", execucao[i], execucao[i+1]); 
    }

    fclose(params);
    fclose(exec);
    free(linha);
    
     // ====================================================================================================================================

    return 0;
}
