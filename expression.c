#include "expression.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree TREE;

// caso desejar, pode alterar o conteúdo das structs abaixo
struct tree {
  char c;
  TREE *left;
  TREE *right;
};

static int number (char c){
    return c-48;
}

TREE *tree_create(){
    TREE *tree = (TREE *) malloc(sizeof(TREE));
    assert(tree != NULL);
    return tree;
}

void tree_read(TREE *tree) {
    char c;
    scanf("%c", &c);
    tree->c = c;
    if (c == '+' || c == '/' || c == '-' || c == '*'){
        tree->left = tree_create();
        tree_read(tree->left);
        tree->right = tree_create();
        tree_read(tree->right);
    }
    else{
        tree->left = NULL;
        tree->right = NULL;
    }
}

void tree_destroy(TREE *tree) {
    if (tree == NULL) return;
    tree_destroy(tree->left);
    tree_destroy(tree->right);
    free(tree);
}

void tree_print(const TREE *tree) {
    if (tree == NULL) return;
    if (tree->c == '+' || tree->c == '/' || tree->c == '-' || tree->c == '*'){
        printf("(");
        tree_print(tree->left);
        printf("%c", tree->c);
        tree_print(tree->right);
        printf(")");
    }
    else printf("%d", number(tree->c));
}

int answer (TREE *root){
    int ans;
    if (root->c == '*') ans = answer(root->left) * answer(root->right);
    else if (root->c == '/') ans = answer(root->left) / answer(root->right);
    else if (root->c == '+') ans = answer(root->left) + answer(root->right);
    else if (root->c == '-') ans = answer(root->left) - answer(root->right);
    else ans = number(root->c);
    return ans;
}
