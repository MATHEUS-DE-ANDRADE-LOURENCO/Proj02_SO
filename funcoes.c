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
            memVirtual[i].processo_id = 0;
        }

        return true;
}

bool inicializarProcesso(Processo *processo, int pid) {
    processo->pid = pid;

    return true;
}

void colocarProcessoNoDisco(Processo discoRigido[TAM_VET], Processo *p) {
    for(int i = 0; i < TAM_VET; i++) {
        if(discoRigido[i].pid == 0) {
            discoRigido[i] = *p;
            return;
        }
    }
}

bool inicializarPagina(Pagina *pagina, int pagina_id, int id_proc) {
    pagina->id = pagina_id;
    pagina->processo_id = id_proc;

    return true;
}

// Inicializa um Frame com base em uma página fornecida como parâmetro
bool inicializarFrame(Frame *frame, Pagina *pag, int id) {
    frame->id = id;
    frame->processo_id = pag->processo_id;
    frame->pagina_id = pag->id;
    
    // Transfere os dados da página para o Frame
    for(int i = 0; i < TAM_VET; i++) {
        frame->dados[i] = pag->dados[i];
    }

    frame->ocupado = false;

    return true;

}

void alocarFrameNaMemoria(Frame *frame, Frame memoria[TAM_VET], int id) {

        if(memoria[id].ocupado == false ) {
            frame->ocupado = true;
            memoria[id] = *frame;
            return;
        }
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

    if(pag.processo_id != 0) {printf("\nPROCESSO_ID: %d", pag.processo_id);}
    else {printf("\nPROCESSO_ID: NONE");}
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

void inicializarTabelaPaginas(Processo *proc) {
    srand(time(NULL));

    for(int i = 0; i < TAM_VET; i++) { 
        proc->tabelaPaginas[i] = rand() % TAM_VET; 
    }
   
}

void colocarPaginaEmMemVirtual(Processo *proc, Pagina memVirtual[TAM_VET]) {
    Pagina pAux;
    
    inicializarPagina(&pAux, 0, 0);

    int paginas_alocadas = 0;

    for(int i = 0; i < TAM_VET && paginas_alocadas < PAGS_PROC; i++) {

        if(memVirtual[i].processo_id == 0) {
            memVirtual[i] = proc->paginas[i];
        }

        paginas_alocadas++;
    }

}

bool temPageFault(Pagina memVirtual[TAM_VET], Frame memFisica[TAM_VET]) {
    bool flag = false;
    bool procura;
    int localPF;

    for(int i = 0; i < TAM_VET; i++) {
        procura = false;
        localPF = i;
        int idVirtual = memVirtual[i].id;
        for(int j = 0; j < TAM_VET; j++) {
            if(memFisica[j].pagina_id == idVirtual) {
                procura = true;
            }
        }
        
        if(procura == false) {
            if (flag == true) flag = false;
            printf("Página de id %d não se encontra na memória física", idVirtual);
        }
    }

    return flag;
}

void imprimirFrame(Frame frame) {
    printf("\n\n-----------------------------------------------");
    printf("\nFRAME %d", frame.id);
    printf("\n-----------------------------------------------");

    if(frame.processo_id != 0) {printf("\nPROCESSO_ID: %d", frame.processo_id);}
    else {printf("\nPROCESSO_ID: NONE");}
    printf("\n-----------------------------------------------");

    if(frame.pagina_id != 0) {printf("\nPROCESSO_ID: %d", frame.pagina_id);}
    else {printf("\nPROCESSO_ID: NONE");}
    printf("\n-----------------------------------------------");

    printf("\nOCUPADO: %d", frame.ocupado);
    printf("\n-----------------------------------------------");
}