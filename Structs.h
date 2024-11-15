// Arquivo structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

#define TAM_VET 100

#include <stdbool.h>

typedef struct {
    int id;
    int processoId;
    int paginaVirtual;
    int paginaReal;
    int estaNaMemoria;  // 1 se estiver na memória real, 0 caso contrário
} Pagina;

typedef struct {
    int pid;
    Pagina paginas[TAM_VET];
    int enderecoVirtual;
} Processo;

typedef struct {
    int id;
    bool ocupado;
    int processo_id;
    int pagina_id;
} Frame;

#endif
