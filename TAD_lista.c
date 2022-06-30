#include "TAD_lista.h"


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*struct noh{
    int elem;
    noh *prox;
};*/

//typedef noh *lista;

lista sequencia_de_jogadas (){ //le as sequencias de jogadas dos jogadores
    lista L = (noh *)malloc(sizeof(noh));
    L->prox = (noh *)malloc(sizeof(noh));
    lista sequencia = L->prox;
    int soma = 0;
    while(soma <= 15){
        scanf("%d", &sequencia->elem);
        sequencia->prox = (noh*)malloc(sizeof(noh));
        soma += sequencia->elem;
        sequencia = sequencia->prox;
    }
    sequencia = NULL;
    /*while(1){
        char lixo;
        scanf("%c", &lixo);
        if(lixo == '\n') break;
    }*/
    return L;
}

/*struct immoblist{
    int l[20];
};*/
//typedef struct immoblist immoblist;

int lista_top(lista L){
    if(L->prox != NULL) return L->prox->elem;
    else return 9999;
}

void lista_delete1st(lista L){
    noh *aux;
    if(L->prox != NULL)
    {
        aux = L->prox;
        L->prox = aux->prox;
        free(aux);
    }
}

immoblist immob_initiate () { //inicia um vetor com o imovel correspondente dentro de cada casa
    immoblist immob;
    for (int i = 0; i < 20; i++) immob.l[i] = i + 1;
    return immob;
}









