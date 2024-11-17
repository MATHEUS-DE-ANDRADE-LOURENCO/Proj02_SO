#include "funcoes.h"

int main(int argc, char *argv[]) {
    // Variáveis de configuração do sistema
    int tamanhoMemoriaReal, tamanhoMemoriaVirtual, processos, tamanhoPaginasProcesso, paginaInicialReal, paginaInicialVirtual;
    int execucao[TAM_VET];

    for(int i = 0; i < TAM_VET; i++) execucao[i] = -1;

    // Inicialização do sistema com dados do arquivo params.csv
    if (!inicializarSistema(&tamanhoMemoriaReal, &tamanhoMemoriaVirtual, &processos, &tamanhoPaginasProcesso, 
                            &paginaInicialReal, &paginaInicialVirtual, "params.csv")) {
        printf("Erro ao ler o arquivo de parâmetros.\n");
        return 1;
    }

    // Carrega a ordem de execução de execucao.csv no vetor execucao
    if (!carregarOrdemExecucao(execucao, "execucao.csv")) {
        printf("Erro ao ler o arquivo de execução.\n");
        return 1;
    }

    // Exibir os valores lidos para verificação
    printf("Configurações do Sistema:\n");
    printf("Memória Real: %d, Memória Virtual: %d\n", tamanhoMemoriaReal, tamanhoMemoriaVirtual);
    printf("Processos: %d, Tamanho de cada página: %d\n", processos, tamanhoPaginasProcesso);
    printf("Página Inicial Real: %d, Página Inicial Virtual: %d\n", paginaInicialReal, paginaInicialVirtual);

    printf("\nOrdem de Execução:\n");
    for (int i = 0; execucao[i] != -1; i += 2) {
        printf("Processo %d, Página %d\n", execucao[i], execucao[i + 1]);
    }

    // Inicializa a memória virtual
    Processo memVirtual[TAM_VET];

    for (int i = 0; i < TAM_VET; i++) {
        memVirtual[i].pid = -1;
    }

    Processo procAux;
    int posMemoriaVirtual = 0;

    // Percorrer o vetor de execução analisando os processos
    for (int i = 0; execucao[i] != -1; i += 2) {
        // Se o processo com esse PID não estiver na memória:
        if (!jaEstaNaMemoriaVirtual(execucao[i], memVirtual)) {
            // Inicializar um processo com esse ID
            procAux.pid = execucao[i];
            procAux.enderecoVirtual = paginaInicialVirtual;

            int posPagina = 0;
            int endPagina = paginaInicialVirtual;
            // Alocando as páginas ao processo
            for(int j = 0; j < tamanhoPaginasProcesso; j++) {
                Pagina pagAux;
                pagAux.id = j;
                pagAux.paginaVirtual = endPagina;
                pagAux.estaNaMemoria = 0;
                pagAux.processoId = execucao[i];

                procAux.paginas[posPagina] = pagAux;
                posPagina++;
                endPagina+=4;
            }

            // Armazena o processo na memória virtual
            memVirtual[posMemoriaVirtual] = procAux;
            posMemoriaVirtual++;  // Incrementa a posição de memória virtual
            paginaInicialVirtual += 4 * tamanhoPaginasProcesso;
        }
    }

    // Imprime a memória virtual
    imprimeMemoriaVirtual(memVirtual, tamanhoPaginasProcesso, posMemoriaVirtual);

    // Inicializa a memória Física
    Frame memReal[TAM_VET];

    for(int i = 0; i < TAM_VET; i++) {
        memReal[i].id = -1;
        memReal[i].pagina_id = -1;
        memReal[i].ocupado = 0;
    }

    printf("\nEstado da memória física: ");
    imprimeMemoriaReal(memReal, tamanhoMemoriaReal);

    // Para cada elemento do vetor de execução
    int posMemReal = 0;
for (int t = 0; execucao[t] != -1; t += 2) {

    printf("\nTempo t = %d", t/2);

    int procAnalisado = execucao[t];
    int pagAnalisada = execucao[t + 1];
    int paginaEncontrada = 0;  // Flag para saber se a página foi encontrada
    Pagina pagAtual;

    // Procurar a página analisada na Memória Virtual
    // Procurar o processo da página
    for (int j = 0; j < TAM_VET && memVirtual[j].pid != -1; j++) {
        // Se encontrar o processo analisado, procurar a página analisada.
        if (memVirtual[j].pid == procAnalisado) {
            for (int k = 0; k < tamanhoPaginasProcesso; k++) {
                sleep(1);    
                // Verifica se a página atual é a página analisada
                if (memVirtual[j].paginas[k].id == pagAnalisada) {
                    pagAtual = memVirtual[j].paginas[k];
                    paginaEncontrada = 1;
                    break;  // Saímos do loop de páginas
                }
            }
        }

        // Se já encontramos a página, podemos sair do loop de processos
        if (paginaEncontrada) {
            break;
        }
    }

    // Verificação se a página foi encontrada
    if (!paginaEncontrada) {
        printf("Página %d do Processo %d não encontrada na Memória Virtual\n", pagAnalisada, procAnalisado);
    } else {
        // Variável para preencher a memória real
        Frame ocupaMemoria;
        // Cria um frame que corresponde a uma página

        ocupaMemoria.id = pagAtual.processoId;
        ocupaMemoria.pagina_id = pagAtual.id;

        //Como o frame ocupará a memória o atributo já será marcado como 1.
        ocupaMemoria.ocupado = 1;

        bool pgFault = pageFault(pagAtual, memReal, tamanhoMemoriaReal);
        
        if(pgFault) {
            pagAtual.paginaReal = posMemReal % 4;
            printf("\n[PAGE FAULT] Página %d do processo %d não está na memória", pagAtual.id, pagAtual.processoId);
            if(memReal[posMemReal % 4].ocupado == 0) {
                printf("\nCarregando página %d do processo %d (endereço lógico %d) no frame %d", pagAtual.id, pagAtual.processoId, pagAtual.paginaVirtual, pagAtual.paginaReal);
            } else {
                printf("\nSubstituindo página %d do processo %d (endereço lógico %d) no frame %d", pagAtual.id, pagAtual.processoId, pagAtual.paginaVirtual, pagAtual.paginaReal);
            }

            memReal[posMemReal%4] = ocupaMemoria;
            posMemReal++;

            printf("\nEstado da memória física: ");
            imprimeMemoriaReal(memReal, tamanhoMemoriaReal);


        } else {
            printf("\nPágina %d do processo %d está na memória física.", pagAtual.id, pagAtual.processoId);
            printf("\nPágina %d do processo %d (endereço lógico %d) no frame %d", pagAtual.id, pagAtual.processoId, pagAtual.paginaVirtual, buscaFrame(pagAtual.processoId, pagAtual.id, memReal, tamanhoMemoriaReal));

            printf("\nEstado da memória física: ");
            imprimeMemoriaReal(memReal, tamanhoMemoriaReal);            
        }
    }

        
}


    return 0;
}
