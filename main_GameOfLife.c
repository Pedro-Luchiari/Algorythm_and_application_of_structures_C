//
// Created by Usuario on 10/10/2021.
//

#include "TAD_lista_contigua.h"
#include "TAD_pilha.h"
#include "TAD_lista.h"
#include <stdio.h>
//#include <assert.h>

int main() {
    immoblist immob;
    immob = immob_initiate();

    lista jogadas1, jogadas2;

    STACK *plr1, *plr2;
    plr1 = stack_create();
    plr2 = stack_create();

    LIST *tab = list_create(); //cria os espaços das casas do tabuleiro
    list_insert(tab, 0, 0);
    int value;
    for (int i = 1; i <= 15; i++) { //define o que cada casa do tabuleiro vai ser
        scanf("%d", &value);
        list_insert(tab, value, i);
    }
    /*for (int i = 0; i <= 15; i++) {
        printf("%d ", tab->p[i]);
    }*/
    jogadas1 = sequencia_de_jogadas(); //lê as jogadas do jogador 1
    jogadas2 = sequencia_de_jogadas(); //lê as jogadas do jogador 2
    noh *l1 = jogadas1->prox;
    noh *l2 = jogadas2->prox;
    /*while (l1 != NULL) {
        printf("%d", l1->elem);
        l1 = l1->prox;
    }
    printf("%d %d", tab->position1, tab->position2);*/

    while (tab->position1 <= 15 || tab->position2 <= 15) {

        if (tab->position1 <= 15 && tab->position2 <= 15) {
            int tabvalue1, tabvalue2;
            move(tab, 1, lista_top(l1));
            move(tab, 2, lista_top(l2));
            lista_delete1st(l1);
            lista_delete1st(l2);
            tabvalue1 = tab->p[tab->position1];
            tabvalue2 = tab->p[tab->position2];
            if (tabvalue1 == -1) {
                stack_push(plr2, stack_top(plr1));
                stack_pop(plr1);
            } else if (tabvalue1 >= 1 && tabvalue1 <= 20) {
                if (immob.l[tabvalue1 - 1] != 0) {
                    stack_push(plr1, tabvalue1);
                    immob.l[tabvalue1 - 1] = 0;
                }
            }

            if (tabvalue2 == -1) {
                stack_push(plr1, stack_top(plr2));
                stack_pop(plr2);
            } else if (tabvalue2 >= 1 && tabvalue2 <= 20) {
                if (immob.l[tabvalue2 - 1] != 0) {
                    stack_push(plr2, tabvalue2);
                    immob.l[tabvalue2 - 1] = 0;
                }
            }
        } else if (tab->position1 <= 15 && tab->position2 > 15) {
            int tabvalue1 = tab->p[tab->position1];
            move(tab, 1, lista_top(l1));
            lista_delete1st(l1);
            if (tabvalue1 == -1) {
                stack_push(plr2, stack_top(plr1));
                stack_pop(plr1);
            } else if (tabvalue1 >= 1 && tabvalue1 <= 20) {
                if (immob.l[tabvalue1 - 1] != 0) {
                    stack_push(plr1, tabvalue1);
                    immob.l[tabvalue1 - 1] = 0;
                }
            }
        } else {
            int tabvalue2 = tab->p[tab->position2];
            move(tab, 2, lista_top(l2));
            lista_delete1st(l2);
            if (tabvalue2 == -1) {
                stack_push(plr1, stack_top(plr2));
                stack_pop(plr2);
            } else if (tabvalue2 >= 1 && tabvalue2 <= 20) {
                if (immob.l[tabvalue2 - 1] != 0) {
                    stack_push(plr2, tabvalue2);
                    immob.l[tabvalue2 - 1] = 0;
                }
            }
        }
    }


    //A partir de agora, começa a parte de printar.
    stack_printBottomUp(plr1);
    stack_printBottomUp(plr2);
    printf("%d", stack_size_compare(plr1, plr2));
}