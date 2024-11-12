// Arquivo funcoes.h
#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdlib.h>

int posicaoPontoVirgula(const char *linha);
void inicializarTabelaDePaginas();
int gerenciarPagina(int processoId, int paginaVirtual);
// Arquivo funcoes.h
int inicializarSistema(int *tamanhoMemoriaReal, int *tamanhoMemoriaVirtual, int *processos, 
                       int *tamanhoPaginasProcesso, int *paginaInicialReal, int *paginaInicialVirtual, 
                       const char *arquivoParams);


int carregarOrdemExecucao(int execucao[TAM_VET], const char *arquivoExecucao);

#endif
