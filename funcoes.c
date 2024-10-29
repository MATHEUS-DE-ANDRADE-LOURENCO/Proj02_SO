# include "funcoes.h"

void inicializarMemoriaFisica(Frame memoriaFisica[]) {
    for(int i = 0; i < TAM_FRAME; i++) {
        memoriaFisica[i].id = 0;
        memoriaFisica[i].ocupado = false;
        memoriaFisica[i].processo_id = 0;
        memoriaFisica[i].pagina_id = 0;
    }
}

void inicializarMemoriaVirtual(Frame memoriaVirtual[]) {
    for(int i = 0; i < TAM_FRAME; i++) {
        memoriaVirtual[i].id = 0;
        memoriaVirtual[i].ocupado = false;
        memoriaVirtual[i].processo_id = 0;
        memoriaVirtual[i].pagina_id = 0;
    }
}
void inicializarTabela(TabelaPaginas tabela[]) {
    for(int i = 0; i < TAM_FRAME; i++) {
        tabela->idFisico = 0;
        tabela-> idVirtual = 0;

        tabela->endFisico = 0;
        tabela->endVirtual = 0;
    }
}