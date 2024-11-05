# ifndef FUNCOES_H

# define FUNCOES_H

# include "Structs.h"
# include <stdio.h>
# include <stdlib.h>

int posicaoPontoVirgula(char *string);

bool inicializarSistema(int *tamanhoMemoriaReal, int *tamanhoMemoriaVirtual, int *processos, int *tamanhoPaginasProcesso, int *paginaInicialReal, int *paginaInicialVirtual, int execucao[TAM_VET], char *params, char *exec);


# endif