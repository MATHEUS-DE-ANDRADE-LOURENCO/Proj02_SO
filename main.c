# include "funcoes.h"

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Favor especificar arquivos da forma correta.");
        return 1;
    }

    FILE *params = fopen(argv[1], "r");
    FILE *exec = fopen(argv[2], "r");

    if(params == NULL || exec == NULL) {
        printf("\nHouve um erro na abertura de algum dos arquivos.");
        return 1;
    } else {
        printf("\nArquivos abertos com sucesso.");
    }

    char *linha;
    linha = (char*) calloc(TAM_VET, sizeof(char));


    int tamanhoMemoriaReal;

    fgets(linha, 3, params);

    tamanhoMemoriaReal = atoi(linha[posicaoPontoVirgula(linha) + 1]);

    printf("%d", tamanhoMemoriaReal);

    return 0;
}