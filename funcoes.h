#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Declaração da função para inicializar a memória física
bool inicializarMemFisica(Frame memFisica[]);

bool inicializarMemVirtual(Pagina memVirtual[]);

bool inicializarProcesso(Processo *processo, int pid);

bool alocarPaginasProc(int paginas_ids[], Processo *proc);

bool inicializarPagina(Pagina *pagina, int pagina_id, int processo_id);

void imprimirPagina(Pagina pag);

void imprimirProcesso(Processo proc);

void inicializarTabelaPaginas(Processo *proc);

void colocarProcessoNoDisco(Processo discoRigido[TAM_VET], Processo *p);

bool inicializarFrame(Frame *frame, Pagina *pag, int id);

void alocarFrameNaMemoria(Frame *frame, Frame memoria[TAM_VET], int id);

void colocarPaginaEmMemVirtual(Processo *proc, Pagina memVirtual[TAM_VET]);

bool temPageFault(Pagina memVirtual[TAM_VET], Frame memFisica[TAM_VET]);

void imprimirFrame(Frame frame);

#endif
