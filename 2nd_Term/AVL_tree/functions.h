#ifndef NSU_LEARNING_FUNCTIONS_H

#define NSU_LEARNING_FUNCTIONS_H

#include <stdio.h>
#include <malloc.h>


#define TREE struct tree


TREE{
    int num;
    TREE * left;
    TREE * right;
};


int max(int num1, int num2){
    if (num1 > num2)
        return num1;
    return num2;
}

int treeHeight(TREE *T){
    if (T == NULL)
        return 0;
    int l_height = treeHeight(T->left);
    int r_height = treeHeight(T->right);

    return max(l_height, r_height) + 1;
}


TREE * rotate_right(TREE * T){
    TREE * child = T->left;
    T->left = child -> right;
    child -> right = T;
    return child;
}


TREE * rotate_left(TREE * T){
    TREE * child = T->right;
    T->right = child -> left;
    child -> left = T;
    return child;
}


int get_balance(TREE * T){ //getting balance of the element
    if (T == NULL)
        return 0;
    return treeHeight(T->right) - treeHeight(T->left);
}


TREE * balance(TREE * T){   //checking for balance and balancing of tree
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
    return balance(T);
}


void del_tree(TREE * T){
    if (T != NULL){
        del_tree(T->right);
        del_tree(T->left);
        free(T);
    }
}


void in_order(TREE * T){
    if (T -> left)
        in_order(T -> left);
    printf("%d\n", T -> num);
    if (T -> right)
        in_order(T -> right);
}


void search_elem(TREE * T, int val){
    if (T == NULL) {
        puts("False");
        return;
    }
    else if (T->num == val)
        puts("True");
    else if (T->num < val)
        search_elem(T->right, val);
    else if (T->num > val)
        search_elem(T->left, val);
}


#endif