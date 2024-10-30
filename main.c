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

}