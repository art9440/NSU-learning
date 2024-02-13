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


void new_height(TREE * T){ //update of height of the element
    T->height = max(get_height(T->left), get_height(T->right)) + 1;
}


TREE * rotate_right(TREE * T){
    TREE * child = T->left;
    T->left = child -> right;
    child -> right = T;
    new_height(T);
    new_height(child);
    return child;
}


TREE * rotate_left(TREE * T){
    TREE * child = T->right;
    T->right = child -> left;
    child -> left = T;
    new_height(T);
    new_height(child);
    return child;
}


int get_balance(TREE * T){ //getting balance of the element
    if (T == NULL)
        return 0;
    return get_height(T->right) - get_height(T->left);
}


TREE * balance(TREE * T){   //checking for balance and balancing of tree
    new_height(T);
    int bal = get_balance(T);
    if (bal == -2){
        if (get_balance(T->left) == 1)
            T->left = rotate_left(T->left);
        return rotate_right(T);
    }
    else if(bal == 2){
        if (get_balance(T->right) == -1) {
            T -> right = rotate_right(T->right);
        }
        return rotate_left(T);
    }
    return T;
}


TREE * create(int number){ //creating element of struct tree
    TREE * cur;
    cur =(TREE*)malloc(sizeof (TREE));
    cur -> height = 0;
    cur -> num = number;
    cur -> right = NULL;
    cur -> left = NULL;
    return cur;
}


TREE * insert(TREE * T, int number){  //inserting element in the tree
    if (number < T -> num){
        if (T -> left == NULL)
            T->left = create(number);
        else
            insert(T -> left, number);
        }
    else if (number >= T -> num) {
        if (T -> right == NULL)
            T->right = create(number);
        else
            insert(T -> right, number);
    }
    new_height(T);
    return balance(T);
}

void del_tree(TREE * T){
    if (T != NULL){
        del_tree(T->right);
        del_tree(T->left);
        free(T);
    }
}

#endif