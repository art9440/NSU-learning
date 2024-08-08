#ifndef NSU_LEARNING_TREE_H

#define NSU_LEARNING_TREE_H

#endif
#include <stdio.h>
#include <malloc.h>

#define TREE struct tree

TREE{
    char* text;
    int num;
    TREE * left;
    TREE * right;
};


TREE * create(char* text, int num){
    TREE * cur;
    cur =(TREE*)malloc(sizeof (TREE));
    cur -> text = text;
    cur -> num = num;
    cur -> right = NULL;
    cur -> left = NULL;
    return cur;

}

void insert(TREE *T, char* text, int num){
    TREE *child;
    if(T != NULL)
    {
        if(T->num * 2 == num) {
            child = create(text,num);
            T->left = child;
        }
        else if(T->num * 2 + 1 == num) {
            child = create(text,num);
            T->right = child;
        }
        else{
            insert(T->left,text,num);
            insert(T->right,text,num);

        }
    }
}

void PreOrder(TREE *T) {
    printf("%d %s\n",T -> num, T -> text);

    if (T -> left != NULL)
        PreOrder(T -> left);
    if (T -> right != NULL)
        PreOrder(T -> right);
}