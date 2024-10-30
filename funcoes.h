#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdbool.h>

// Declaração da função para inicializar a memória física
bool inicializarMemFisica(Frame memFisica[]);

bool inicializarMemVirtual(Pagina memVirtual[]);

#endif
