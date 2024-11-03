# include "funcoes.h"

int main() {
    // Inicializa as memórias Principal e Virtual
    Frame memPrincipal[TAM_VET];
    Pagina memVirtual[TAM_VET];
    Processo discoRigido[TAM_VET];

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

    // Cria um processo de três páginas, com o conteúdo ids presentes no vetor idPaginasP1.
    
    Processo p1;

    int idPaginasP1[PAGS_PROC] = {2, 1, 4};

    inicializarProcesso(&p1, 12);
    
    // Insere as páginas do vetor no processo
    alocarPaginasProc(idPaginasP1, &p1);

    // Inicializa a tabela de páginas do processo

    inicializarTabelaPaginas(&p1);
    
    // Coloca as páginas do processo p1 na memória virtual.
    colocarPaginaEmMemVirtual(&p1, memVirtual);
    
    
    // Cria um frame para cada página da memória virtual.
    for(int i = 0; i < TAM_VET; i++) {

        Frame frame;
        int idFisico = p1.tabelaPaginas[memVirtual[i].id];
       
        inicializarFrame(&frame, &memVirtual[i], idFisico);

        alocarFrameNaMemoria(&frame, memPrincipal, idFisico);

        imprimirFrame(memPrincipal[idFisico]);
    }

    

    if(temPageFault(memVirtual, memPrincipal)) printf("PAGE FAULT: Sim");
    else printf("Page Fault: Não");


    return 0;
}