# include "funcoes.h"

int main() {
    Frame memPrincipal[100];
    Pagina memVirtual[100];

    if(inicializarMemFisica(memPrincipal)) {
        printf("\nMemória física inicializada com sucesso!");
    } else {
        printf("\nHouve um erro ao inicializar a memória física!");
    }

    if(inicializarMemVirtual(memVirtual)) {
        printf("\nMemória virtual inicializada com sucesso!");
    } else {
        printf("\nHouve um erro ao inicializar a memória virtual!");
    }

    Processo p1;
    int idPaginasP1[PAGS_PROC] = {2, 7, 4};

    inicializarProcesso(&p1, 12);

    alocarPaginasProc(idPaginasP1 , &p1);

    imprimirProcesso(p1);

    return 0;
}