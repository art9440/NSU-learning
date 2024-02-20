#include <stdio.h>
#include "functions.h"
#include <string.h>


void orders(char* answer, TREE * avl_tree){
    if (strcmp(answer, "postorder") == 0)
        post_order(avl_tree);
    else if (strcmp(answer, "preorder") == 0)
        pre_order(avl_tree);
    else if (strcmp(answer, "inorder") == 0)
        in_order(avl_tree);
    else
        puts("incorrect input.");
}


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
            avl_tree = insert(avl_tree,number);
        }
    }
    printf("%d\n", get_height(avl_tree) + 1);
    puts("What order do you want?");
    char answer[10];
    scanf("%s", &answer);
    orders(answer, avl_tree);
    del_tree(avl_tree);

    return 0;
}