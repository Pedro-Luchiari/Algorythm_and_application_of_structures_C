#include"TAD_pilha.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct stack STACK;

/*struct stack
{
    int elem;
    STACK *prox;
};*/

STACK *stack_create(void)
{
    STACK *pilha;
    pilha = (STACK*)malloc(sizeof(STACK));
    assert (pilha != NULL);
    pilha->prox = NULL;
    return pilha;
}

void stack_destroy(STACK *pilha)
{
    STACK *aux;
    while(pilha->prox != NULL)
    {
        aux = pilha->prox;
        pilha->prox = aux->prox;
        free(aux);
    }
    free(pilha);
}

bool stack_isEmpty(const STACK *pilha)
{
    if(pilha->prox == NULL) return true;
    else return false;
}

int stack_top(const STACK *pilha)
{
    if(pilha->prox != NULL) return pilha->prox->elem;
    else return 99999;
}

void stack_push(STACK *pilha, int element)
{
    STACK *aux;
    aux = (STACK*)malloc(sizeof(STACK));
    aux->prox = pilha->prox;
    pilha->prox = aux;
    aux->elem = element;
}

void stack_pop(STACK *pilha)
{
    STACK *aux;
    if(pilha->prox != NULL)
    {
        aux = pilha->prox;
        pilha->prox = aux->prox;
        free(aux);
    }
}

STACK *stack_reverse(STACK *pilha)
{
    STACK *P = stack_create();
    STACK *Pi = stack_create();
    while(!stack_isEmpty(pilha))
    {
        stack_push(P, stack_top(pilha));
        stack_push(Pi, stack_top(pilha));
        stack_pop(pilha);
    }
    while(!stack_isEmpty(Pi))
    {
        stack_push(pilha, stack_top(Pi));
        stack_pop(Pi);
    }
    stack_destroy(Pi);
    return P;
}

void stack_printTopDown(STACK *pilha)
{
    STACK *P = stack_create();
    while(!stack_isEmpty(pilha))
    {
        printf("%d ", stack_top(pilha));
        stack_push(P, stack_top(pilha));
        stack_pop(pilha);
    }
    while(!stack_isEmpty(P))
    {
        stack_push(pilha, stack_top(P));
        stack_pop(P);
    }
    stack_destroy(P);
    printf("\n");
}

void stack_printBottomUp(STACK *pilha)
{
    if (stack_isEmpty(pilha)){
        int answer = 0;
        printf ("%d\n", answer);
    }
    else {
        STACK *P = stack_reverse(pilha);
        stack_printTopDown(P);
    }
}

int stack_size (STACK *pilha){
    STACK *P = pilha->prox;
    int t = 0;
    while (P != NULL){
        t++;
        P = P->prox;
    }
    return t;
}

int stack_size_compare (STACK *pilha1, STACK *pilha2){
    if (stack_size(&(*pilha1)) > stack_size(&(*pilha2))) return 1;
    else if (stack_size(&(*pilha1)) < stack_size(&(*pilha2))) return 2;
    else return 3;
}

















