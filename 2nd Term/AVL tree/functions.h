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

int max(int num1, int num2){
    if (num1 > num2)
        return num1;
    return num2;
}

void balance(TREE * T){

}

int get_height(TREE * T){
    if (T == NULL)
        return -1;
    return T->height;
}

int new_height(TREE * T){
    if (T == NULL)
        return 0;
    return max(get_height(T->left), get_height(T-> right)) + 1;
}

int vol_balance(TREE * T){
    return get_height(T->right) - get_height(T->left);
}

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
        balance(T);
        new_height(T);
    }
}

#endif
