#include <stdio.h>
#include "functions.h"

int main(){
    int num_of_tops, number, height = 0;
    TREE * avl_tree;
    scanf("%d", &num_of_tops);
    for (int i = 0; i < num_of_tops; i++){
        scanf("%d", &number);
        if (height == 0) {
            avl_tree = create(height, number);
            height++;
        }
        else {
            insert(avl_tree, height, number);
            if (balance_factor(avl_tree) == 0);
        }
    }

}
