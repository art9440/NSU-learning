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


int get_height(TREE * T){
    if (T == NULL)
        return -1;
    return T->height;
}


void new_height(TREE * T){
    T->height = max(get_height(T->left), get_height(T->right)) + 1;
}


void rotate_right(TREE * T){
    TREE * child = T->left;
    T->left = child -> right;
    child -> right = T;
    new_height(child);
    new_height(T);
}


void rotate_left(TREE * T){
    TREE * child = T->right;
    T->right = child -> left;
    child -> left = T;
    new_height(child);
    new_height(T);
}


int get_balance(TREE * T){
    if (T == NULL)
        return 0;
    return get_height(T->right) - get_height(T->left);
}


void balance(TREE * T){
    int bal = get_balance(T);
    if (bal == -2){
        if (get_balance(T->left) == 1)
            rotate_left(T);
        rotate_right(T);
    }
    else if(bal == 2){
        if (get_balance(T->left) == -1)
            rotate_right(T);
        rotate_left(T);
    }
}


TREE * create(int number){
    TREE * cur;
    cur =(TREE*)malloc(sizeof (TREE));
    cur -> height = 1;
    cur -> num = number;
    cur -> right = NULL;
    cur -> left = NULL;
    return cur;
}


void insert(TREE * T, int number){
    TREE * child;
        if (number < T -> num){
            if (T -> left == NULL) {
                child = create(number);
                T->left = child;
            }
            else
                insert(T -> left, number);
        }
        else if (number >= T -> num) {
            if (T -> right == NULL) {
                child = create(number);
                T->right = child;
            }
            else
                insert(T -> right, number);
        }
        new_height(T);
        balance(T);
}

#endif
