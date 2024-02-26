#include <stdio.h>
#include "functions.h"



int main(){
    int num_of_tops, number, val;
    TREE * avl_tree;
    scanf("%d", &num_of_tops);
    for (int i = 0; i < num_of_tops; i++){
        scanf("%d", &number);
        if (avl_tree == NULL) {
            avl_tree = create(number);
        }
        else {
            avl_tree = insert(avl_tree,number);
        }
    }
    printf("%d\n", treeHeight(avl_tree));

    puts("In order");
    in_order(avl_tree);

    puts("What number do you want to find?");
    scanf("%d", &val);
    search_elem(avl_tree, val);

    del_tree(avl_tree);

    return 0;
}