#include "TAD_lista_contigua.h"

#include <stdlib.h>




/*struct list  //criacao da estrutura list
{
    int *p;
    int position1, position2;
};*/


LIST *list_create()
{
    LIST *L;
    L = (LIST *) malloc(sizeof(LIST));
    L->p = (int *) malloc(16 * sizeof(int));
    L->position1 = 0;
    L->position2 = 0;
    return L;
}

void list_insert (LIST *List, int value, int idx){
    List->p[idx] = value;
}


void move (LIST *L, int plr, int dice){
    if (plr == 1) L->position1 += dice;
    else L->position2 += dice;
}

void list_destroy (LIST *L){
    free(L);
}


