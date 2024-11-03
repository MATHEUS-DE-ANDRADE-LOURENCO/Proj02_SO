#ifndef STRUCTS_H
#define STRUCTS_H

#define TAM_VET 5
#define PAGS_PROC 3
#include <stdbool.h>

typedef struct {
    int id;
    int processo_id;
    int frame_id;
    char dados[TAM_VET];
} Pagina;

typedef struct {
    int pid;
    int tabelaPaginas[TAM_VET];
    Pagina paginas[PAGS_PROC];
} Processo;

typedef struct {
    int id;
    bool ocupado;
    int processo_id;
    int pagina_id;
    char dados[TAM_VET];
} Frame;

#endif
