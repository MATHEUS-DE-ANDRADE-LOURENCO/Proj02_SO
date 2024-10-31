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

bool inicializarProcesso(Processo *processo, int pid) {
    processo->pid = pid;

    return true;
}

bool inicializarPagina(Pagina *pagina, int pagina_id, int id_proc) {
    pagina->id = pagina_id;
    pagina->processo_id = id_proc;

    return true;
}

bool alocarPaginasProc(int paginas_ids[], Processo *proc) {
    Pagina pAux;
    for(int i = 0; i < PAGS_PROC; i++) {
        inicializarPagina(&pAux, paginas_ids[i], proc->pid);
        proc->paginas[i] = pAux;
    }

    return true;
}

void imprimirPagina(Pagina pag) {
    printf("\n\n-----------------------------------------------");
    printf("\nPAGINA %d", pag.id);
    printf("\n-----------------------------------------------");

    printf("\nOCUPADO?: %d", pag.ocupado);

    if(pag.processo_id = 0) {
        printf("\nPROCESSO_ID: NONE");
    } else {
        printf("\nPROCESSO_ID: %d", pag.processo_id);
    }

    printf("\n-----------------------------------------------");
}

void imprimirProcesso(Processo proc) {
    printf("\n\n-----------------------------------------------");
    printf("\nPROCESSO %d", proc.pid);
    printf("\n-----------------------------------------------");

    for(int i = 0; i < PAGS_PROC; i++) {
        imprimirPagina(proc.paginas[i]);
    }
    printf("\n-----------------------------------------------");
}

