#ifndef NSU_LEARNING_STACK_H
#define NSU_LEARNING_STACK_H

#define STACK struct stack
#include <malloc.h>
#include <stdio.h>


STACK{
    int value;
    STACK * next;
};


STACK* create(int value){ //создаем элемент списка
    STACK * elem;
    elem = (STACK*)malloc(sizeof (STACK));
    elem -> value = value;
    elem -> next = NULL;
    return elem;
}

void push(STACK * L, STACK * elem){ //добавить элемент в список
    STACK * first = L -> next;
    elem -> next = first;
    L -> next = elem;
}


int empty(STACK *L){ //проверка списка на пустоту
    if (L -> next)
        return 0;
    return 1;
}

int pop(STACK * L){ //удаление элемента из списка и получение его значения
    if (!empty(L)){
        STACK * old =L -> next;
        L -> next = old -> next;
        int r = old -> value;
        free(old);
        return r;
    }
    return 0;
}


int get(STACK * L){ //получить значение верхнего элемента
    if (!empty(L)){
        STACK * cur = L -> next;
        int r = cur -> value;
        return r;
    }
    return 0;
}

#endif
