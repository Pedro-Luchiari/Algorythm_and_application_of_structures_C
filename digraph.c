#include "digraph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;

struct edge {
    int index;
    EDGE *next;
};

struct digraph {
    int order;
    EDGE **vertex;
};

DIGRAPH *digraph_read()
{
    int order, u, v;
    scanf("%d", &order);
    DIGRAPH *digraph = digraph_create(order);
    while (scanf("%d %d", &u, &v) != EOF && u!=999)
    {
        digraph_add_edge(digraph, u, v);
    }
    return digraph;
}


DIGRAPH *digraph_create(int order) {
    DIGRAPH *G = (DIGRAPH *)malloc(sizeof(DIGRAPH));
    G->order = order;
    G->vertex = (EDGE**)malloc(order * sizeof(EDGE*));

    for (int i=0; i<order; ++i)
        G->vertex[i] = NULL;
    return G;
}

void digraph_destroy(DIGRAPH *digraph)
{
    for(int i = 0; i<=digraph->order;i++)
    {
        EDGE *aux;
        while(digraph->vertex[i] != NULL)
        {
            aux = digraph->vertex[i]->next;
            digraph->vertex[i] = aux->next;
            free(aux);
        }
    }
    free(digraph->vertex);
    free(digraph);
}

void digraph_add_edge(DIGRAPH *digraph, int u, int v) {

    EDGE *temp = (EDGE *)malloc(sizeof(EDGE));
    temp->index = v;
    temp->next = NULL;
    if(digraph->vertex[u] == NULL)digraph->vertex[u]->next =temp;
    else
    {
        EDGE *aux;
        for(aux = digraph->vertex[u];aux->next != NULL;aux = aux->next);
        aux->next = temp;
    }
}

bool digraph_has_edge(const DIGRAPH *digraph, int u, int v) {
    EDGE *temp = digraph->vertex[u]->next;
    while(temp->index < v && temp != NULL){
        temp = temp->next;
    }
    if(temp->index == v && v != u)return true;
    else return false;
}

typedef enum { WHITE, GRAY, BLACK } COLOR;

// Returns false if is not dag
static bool topological_sort_dfs(const DIGRAPH *digraph, int u, COLOR *color, STACK *stack) {
    color[u] = GRAY;
    bool aux = true;
    for (int i = 0; i < digraph->order && aux == true; i++){
        if (digraph_has_edge(digraph, u, i)){
            if (color[i] == WHITE){
                aux = topological_sort_dfs(digraph, i, color, stack);
            }
            else if (color[i] == GRAY) return false;
        }
    }
    color[u] = BLACK;
    stack_push(stack, u);
    return aux;
}

void topological_sort(const DIGRAPH *digraph) {
    bool is_dag = true;
    COLOR *color = (COLOR *) malloc(digraph->order * sizeof (COLOR));
    for (int i = 0; i < digraph->order; i++) color[i] = WHITE;
    STACK *stack = stack_create();
    for (int i = 0; i < digraph->order && is_dag == true; i++) {
        if (color[i] == WHITE){
            is_dag = topological_sort_dfs(digraph, i, color, stack);
        }
    }
    if (is_dag){
        while (!stack_isEmpty(stack)){
            printf("%d ", stack_top(stack));
            stack_pop(stack);
        }
    }
    printf("\n");
    stack_destroy(stack);
    free(color);
}
