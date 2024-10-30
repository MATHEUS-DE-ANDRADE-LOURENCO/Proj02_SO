# include "funcoes.h"

bool inicializarMemFisica(Frame memFisica[]) {
    for (int i = 0; i < TAM_VET; i++) {
        memFisica[i].id = 0;
        memFisica[i].ocupado = false;
        memFisica[i].pagina_id = 0;
        memFisica[i].processo_id = 0;
    }

    return true;
} 

bool inicializarMemVirtual(Pagina memVirtual[]) {
        for (int i = 0; i < TAM_VET; i++) {
            memVirtual[i].frame_id = 0;
            memVirtual[i].id = 0;
            memVirtual[i].ocupado = 0;
            memVirtual[i].processo_id = 0;
        }

        return true;
}