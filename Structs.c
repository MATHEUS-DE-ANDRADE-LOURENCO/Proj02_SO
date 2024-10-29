# include <stdbool.h>

typedef struct{
    int id;
    bool ocupado;
    int processo_id;
    int pagina_id;
    char dados[100];
}Frame;

typedef struct{
    int idFisico;
    int idVirtual;

    int endFisico;
    int endVirtual;
} TabelaPaginas;