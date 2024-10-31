#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdbool.h>

// Declaração da função para inicializar a memória física
bool inicializarMemFisica(Frame memFisica[]);

bool inicializarMemVirtual(Pagina memVirtual[]);

bool inicializarProcesso(Processo *processo, int pid);

bool alocarPaginasProc(int paginas_ids[], Processo *proc);

bool inicializarPagina(Pagina *pagina, int pagina_id, int processo_id);

void imprimirPagina(Pagina pag);

void imprimirProcesso(Processo proc);
#endif
