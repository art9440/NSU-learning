#ifndef NSU_LEARNING_FUNCTIONS_H

#define NSU_LEARNING_FUNCTIONS_H

#include <stdio.h>
#include <malloc.h>

#define TREE struct tree

TREE{
    int num;
    int height;
    TREE * left;
    TREE * right;
};


TREE * create(int height, int number){
    TREE * cur;
    cur =(TREE*)malloc(sizeof (TREE));
    cur -> height = height + 1;
    cur -> num = number;
    cur -> right = NULL;
    cur -> left = NULL;
    return cur;
}


void insert(TREE * T, int height, int number){
    TREE * child;
    if (T != NULL){
        if (number < T -> num){
            if (T -> left == NULL) {
                child = create(height, number);
                T->left = child;
            }
            else
                insert(T -> left, height + 1, number);
        }
        else if (number >= T -> num) {
            if (T -> right == NULL) {
                child = create(height, number);
                T->right = child;
            }
            else
                insert(T -> right, height + 1, number);
        }
    }
}

int balance_factor(TREE * T){

}


#endif
