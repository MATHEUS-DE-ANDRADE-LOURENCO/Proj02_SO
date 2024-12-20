// Arquivo funcoes.h
#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int posicaoPontoVirgula(const char *linha);
// Arquivo funcoes.h
int inicializarSistema(int *tamanhoMemoriaReal, int *tamanhoMemoriaVirtual, int *processos, 
                       int *tamanhoPaginasProcesso, int *paginaInicialReal, int *paginaInicialVirtual, 
                       const char *arquivoParams);


int carregarOrdemExecucao(int execucao[TAM_VET], const char *arquivoExecucao);

bool jaEstaNaMemoriaVirtual(int pid, Processo memoriaVirtual[TAM_VET]);

bool pagEstaNoProc(int id, Processo p, int tamanhoPaginasProcesso);

void imprimeMemoriaVirtual(Processo memoriaVirtual[TAM_VET], int tamanhoPaginasProcesso, int qtdProcessos);

void imprimeMemoriaReal(Frame memReal[TAM_VET], int tamanhoMemoriaReal);

bool pageFault(Pagina pag, Frame memReal[TAM_VET], int tamanhoMemoriaReal);

int buscaFrame(int id, int pagina_id, Frame memReal[TAM_VET], int tamanhoMemoriaReal);

#endif
