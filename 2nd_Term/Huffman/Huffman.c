#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <uchar.h>
#include <locale.h>

#define QUEUE struct queue
#define NODE struct node
#define FIRST_MEET 1

NODE{
    wchar_t symbol;
    long int freq;
    NODE * left;
    NODE * right;
};


QUEUE{
    int size;
    NODE ** heap_for_huffman;
};

void Creating_queue(QUEUE * queue){
    queue = (QUEUE*) malloc(sizeof(QUEUE));
    queue->size = 0;
    queue->heap_for_huffman = NULL;
}


void reading_file(FILE * input) {
    wchar_t symbol;
    QUEUE *priority_queue = NULL;
    Creating_queue(priority_queue);
    while ((symbol = fgetwc(input)) != WEOF) {
        int check_in_queue = 0;
        for (int i = 0; i < priority_queue->size; i++){
            if ()
        }
    }
}


int main(){
    setlocale(LC_ALL, "");
    FILE * input = fopen("in.txt", "r, ccs=UTF-8");
    FILE * output = fopen("out.txt", "w, ccs=UTF-8");
    reading_file(input);




    return 0;
}
