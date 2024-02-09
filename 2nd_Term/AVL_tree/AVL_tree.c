#include <stdio.h>
#include "functions.h"

int main(){
    int num_of_tops, number, height = 0;
    TREE * avl_tree;
    scanf("%d", &num_of_tops);
    for (int i = 0; i < num_of_tops; i++){
        scanf("%d", &number);
        if (avl_tree == NULL) {
            avl_tree = create(height, number);
        }
        else {
            insert(avl_tree, height, number);
        }
    }
    printf("%d", get_height(avl_tree) + 1);
}
