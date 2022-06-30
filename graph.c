#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int infinite = 9999;

typedef struct neighbor NEIGHBOR;
struct neighbor{
    int index;
    int weight;
    NEIGHBOR *next;
};

struct graph {
    int order;
    NEIGHBOR **neighbors;
};

GRAPH *graph_read() {
    int order;
    scanf("%d", &order);
    GRAPH *graph;
    graph = graph_create(order);
    int n1, n2, w;
    while(scanf("%d%d%d", &n1, &n2, &w) != EOF && n1 != 999){
        graph_add_edge(graph, n1, n2, w);
        graph_add_edge(graph, n2, n1, w);
    }
    return graph;
}

GRAPH *graph_create(int order) {
    GRAPH *g = (GRAPH *)malloc(sizeof(GRAPH));
    assert(g!=NULL);
    g->order = order;
    g->neighbors = (NEIGHBOR **) malloc(order * sizeof (NEIGHBOR *));
    assert(g->neighbors != NULL);
    for(int i = 0; i < g->order; ++i){
        g->neighbors[i] = NULL;
    }
    return g;
}

void graph_destroy(GRAPH *graph) {
    for (int i = 0; i < graph->order; i++){
        while (graph->neighbors[i] != NULL) {
            NEIGHBOR *aux = graph->neighbors[i];
            graph->neighbors[i] = aux->next;
            free(aux);
        }
    }
    free(graph->neighbors);
    free(graph);
}

void graph_add_edge(GRAPH *graph, int u, int v, int w) {
    NEIGHBOR *aux;
    aux = (NEIGHBOR*) malloc (sizeof(NEIGHBOR));
    aux->index = v;
    aux->weight = w;
    aux->next = NULL;
    if (graph->neighbors[u] == NULL){
        graph->neighbors[u] = aux;
    }
    else{
        NEIGHBOR *aux2 = graph->neighbors[u];
        while(aux2->next != NULL){
            aux2 = aux2->next;
        }
        aux2->next = aux;
    }
}

//a função abaixo é de teste
/*bool graph_has_edge(const GRAPH *graph, int u, int v) {
    if (u != v) {
        int lower = (u < v) ? u : v;
        int greater = (u > v) ? u : v;
        NEIGHBOR *aux;
        aux = graph->neighbors[lower];
        while (aux != NULL && aux->index < greater) {
            aux = aux->next;
        }
        if (aux != NULL && aux->index == greater) return true;
        return false;
    }
    return true;
}*/

int graph_edge_weight(const GRAPH *graph, int u, int v) {
    if (u != v) {
        int lower = (u < v) ? u : v;
        int greater = (u > v) ? u : v;
        NEIGHBOR *aux;
        aux = graph->neighbors[lower];
        while (aux->index < greater) {
            aux = aux->next;
        }
        return aux->weight;
    }
    return 0;
}

//a função abaixo é de teste;
/*void graph_print(const GRAPH *graph) {
    for (int u = 0; u < graph->order; ++u) {
        for (int v = 0; v < graph->order; ++v) {
            if (graph_has_edge(graph, u, v)) printf("%d  ", graph_edge_weight(graph, u, v));
            else printf("inf ");
        }
        printf("\n");
    }
}*/

bool all_visited (GRAPH *graph, int *visited){ //verifica se todos os nós já foram visitados
    for (int i = 0; i < graph->order; i++){
        if (visited[i] == 0) return false;
    }
    return true;
}

int find_minimum (GRAPH *graph, int *visited, int *distance){ //verifica o nó de menor caminho até o 0;
    int min = infinite + 1;
    int index;
    for (int i = 0; i < graph->order; i++){
        if (distance[i] < min && visited[i] == 0){
            min = distance[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(GRAPH *graph, int u){
    //declaração dos arrays:
    int *prev = (int *) malloc(graph->order * sizeof(int));
    int *distance = (int *) malloc(graph->order * sizeof(int));
    int *visited = (int *) malloc(graph->order * sizeof(int));

    //inicialização dos arrays:
    distance[u] = 0;
    prev[u] = -1;
    for (int i = 1; i < graph->order; i++) distance[i] = infinite;
    for (int i = 0; i < graph->order; i++) visited[i] = 0;

    //O algoritmo:
    while (!all_visited(graph, visited)){
        int v = find_minimum(graph, visited, distance);
        for (NEIGHBOR *aux = graph->neighbors[v]; aux != NULL; aux = aux->next){
            if (distance[v] + graph_edge_weight(graph, v, aux->index) < distance[aux->index]){
                distance[aux->index] = distance[v] + graph_edge_weight(graph, v, aux->index);
                prev[aux->index] = v;
            }
        }
        visited[v] = 1;
    }

    //Impressão das sequências usando pilhas e das distâncias:
    for (int i = 1; i < graph->order; i++) {
        if (graph->neighbors[i] != NULL && distance[i] != infinite) {
            STACK *sequence = stack_create();
            stack_push(sequence, i);
            int p = prev[i];
            while (p != 0) {
                stack_push(sequence, p);
                p = prev[p];
            }
            stack_push(sequence, 0);
            while (!stack_isEmpty(sequence)) {
                printf("%d ", stack_top(sequence));
                stack_pop(sequence);
            }
            printf(": %d\n", distance[i]);
            stack_destroy(sequence);
        }
    }
    free(distance);
    free(prev);
    free(visited);
}
