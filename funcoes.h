#ifndef funcoes

#define funcoes

# include "Structs.c"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define TAM_FRAME 4096
# define NUM_FRAMES 100

void inicializarMemoriaFisica(Frame memoriaFisica[]);
void inicializarMemoriaVirtual(Frame memoriaVirtual[]);
void inicializarTabela(TabelaPaginas tabela[]);

#endif