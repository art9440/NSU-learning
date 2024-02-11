#include <stdio.h>
#include "functions.h"

int main(){
    int num_of_tops, number;
    TREE * avl_tree;
    scanf("%d", &num_of_tops);
    for (int i = 0; i < num_of_tops; i++){
        scanf("%d", &number);
        if (avl_tree == NULL) {
            avl_tree = create(number);
        }
        else {
            insert(avl_tree,number);
        }
    }
    printf("%d", get_height(avl_tree) + 1);

    return 0;
}
