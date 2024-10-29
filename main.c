# include "funcoes.h"

int main() {
    
    Frame memoriaFisica[NUM_FRAMES];
    Frame memoriaVirtual[NUM_FRAMES];
    TabelaPaginas tabela[NUM_FRAMES];

    
    inicializarMemoriaFisica(memoriaFisica);
    inicializarMemoriaVirtual(memoriaVirtual);
    inicializarTabela(tabela);


    return 0;
}