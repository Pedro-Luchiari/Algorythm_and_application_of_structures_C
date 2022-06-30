#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree TREE;

struct tree {
    int info;
    TREE *left, *right;
};

struct bst {
    TREE *root;
};

BST *bst_create() {
    BST *bst;
    bst = (BST *)malloc(sizeof(BST));
    assert (bst!=NULL);
    bst->root = NULL;
    return bst;
}

static void tree_destroy(TREE *tree) { //percorre toda a arvore recursivamente, liberando toda a memoria
    if (tree == NULL) return;
    tree_destroy(tree->left);
    tree_destroy(tree->right);
    free(tree);
}

void bst_destroy(BST *bst) {
    tree_destroy(bst->root);
    free(bst);
}

static TREE *tree_create(int value) {
    TREE *root;
    root = (TREE *)malloc(sizeof (TREE));
    assert(root != NULL);
    root->left = root->right = NULL;
    root->info = value; //inicia o unico elemento com o valor value
    return root;
}

static TREE *tree_insert(TREE *tree, int value) {
    if(tree == NULL) { //insere o primeiro elemento, com os filhos sendo NULL
        tree = (TREE *) malloc(sizeof(TREE));
        assert(tree != NULL);
        tree->left = NULL;
        tree->right = NULL;
        tree->info = value;
    }
    else if (value < tree->info) {
        if (tree->left == NULL){ //encontrou a posicao certa para inserir
            tree->left = (TREE *) malloc(sizeof(TREE));
            assert(tree->left != NULL);
            tree->left->left = NULL;
            tree->left->right = NULL;
            tree->left->info = value;
        }
        else {
            tree_insert(tree->left, value); //procura recursivamente a posicao certa
        }
    }
    else if (value > tree->info){
        if (tree->right == NULL){ //encontrou a posicao certa para inserir
            tree->right = (TREE *) malloc(sizeof(TREE));
            assert(tree->right != NULL);
            tree->right->right = NULL;
            tree->right->left = NULL;
            tree->right->info = value;
        }
        else {
            tree_insert(tree->right, value); //procura recursivamente a posicao certa
        }
    }
    return tree;
}

void bst_insert(BST *bst, int value) {
    if (bst->root == NULL){
        bst->root = tree_create(value);
        return;
    }
    bst->root = tree_insert(bst->root, value);
}

static TREE *left_most_child(TREE *tree) {
    if (tree->left == NULL) return tree; //significa que ja chegou na crianca mais a esquerda
    else return left_most_child(tree->left); //continua indo pra esquerda (recursivamente)
}

static bool tree_search(const TREE *tree, int value) {
    if (tree == NULL) return false; //ja percorremos toda a arvore e nao achamos
    else {
        if (value < tree->info) return tree_search(tree->left, value); //vai pra esquerda recursivamente
        else if (value > tree->info) return tree_search(tree->right, value); //vai pra direita recursivamente
        else return true; //significa que tree->info = value, ou seja, value se encontra na BST
    }
}

static TREE *tree_remove(TREE *tree, int value) {
    if (tree == NULL) return tree; //nao ha o que remover
    else {
        if (value < tree->info) tree->left = tree_remove(tree->left, value);
            //vai indo pra esquerda ate achar quem se deve remover
        else if (value > tree->info) tree->right =  tree_remove(tree->right, value);
            //vai indo pra direita ate achar quem se deve remover
        else if (tree->left == NULL && tree->right == NULL) { //a partir daqui, ja se achou o elemento a ser removido
            //esse eh o caso mais simples, pois nao ha filhos
            free(tree);
            tree = NULL;
        }
        else if (tree->left == NULL) { //nesse caso, ha o filho direito. Remocao parecida com TADs lineares
            TREE *ptr = tree;
            tree = tree->right;
            free(ptr);
        }
        else if (tree->right == NULL) { //nesse caso, ha o filho esquerdo. Remocao parecida com TADs lineares
            TREE *ptr = tree;
            tree = tree->left;
            free(ptr);
        }
        else { //ambos os filhos presentes. Substituimos pelo menor descendente à direita, por convencao.
            TREE *ptr = left_most_child(tree->right);
            tree->info = ptr->info;
            tree->right = tree_remove(tree->right,ptr->info); //remove-se o menor elemento à direita de onde ele estava
        }
    }
    return tree;
}

void bst_remove(BST *bst, int value) {
    tree_remove(bst->root, value);
}

bool bst_search(const BST *bst, int value) {
    return tree_search(bst->root, value);
}

static int tree_height(const TREE *tree/*, int height*/) {
    if (tree == NULL) return 0;
    return (tree_height(tree->left) > tree_height(tree->right)) ? tree_height(tree->left) + 1 : tree_height(tree->right) + 1;
    //chamada recursiva: para cada subarvore, calcula-se a altura pela maior altura entre a subarvore da esquerda e a da direita,
    //incrementando-se em uma unidade a altura em cada recursao.
}

int bst_height(const BST *bst) {
    return tree_height(bst->root) - 1; //precisamos diminuir em uma unidade, pois a recursao anterior fornece uma altura com uma unidade a mais.
}

static void tree_print(const TREE *tree) {
    printf("(");
    if(tree == NULL){
        printf(")"); //Toda vez que vamos voltar a niveis anteriores, printamos ")".
        return;
    }
    printf("%d", tree->info);
    tree_print(tree->left); //recursao
    tree_print(tree->right); //recursao
    printf(")");
}

void bst_print(const BST *bst) {
    tree_print(bst->root);
}
