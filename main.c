#include <stdio.h>

#include "expression.h"

int main() {
    TREE *tree = tree_create();
    tree_read(tree);
    tree_print(tree);
    printf(" = %d\n", answer(tree));
    tree_destroy(tree);
}
