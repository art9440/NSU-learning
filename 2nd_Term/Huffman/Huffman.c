#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <uchar.h>
#include <locale.h>

#define QUEUE struct queue
#define NODE struct node

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


void print_queue(QUEUE * queue){
    for (int i = 0; i < queue->size; i++){
        wchar_t s = queue->heap_for_huffman[i]->symbol;
        long int f = queue->heap_for_huffman[i]->freq;
        printf("%lc --- %ld", s, f);
    }
}


void update_size(QUEUE * queue){
    queue->size++;
    queue->heap_for_huffman = realloc(queue->heap_for_huffman,
                    queue->size * sizeof(NODE*));
}


void add_node(wchar_t symbol, QUEUE * queue){
    NODE * new_node = (NODE*)malloc(sizeof(NODE));
    new_node->symbol = symbol;
    new_node->freq = 1;
    new_node->right = NULL;
    new_node->left = NULL;
    int index = queue->size - 1;
    queue->heap_for_huffman[index] = new_node;

    while (index > 0 && queue->heap_for_huffman[index]
    >= queue->heap_for_huffman[index-1]){
        NODE * temp =  queue->heap_for_huffman[index];
        queue->heap_for_huffman[index] =
                queue->heap_for_huffman[index - 1];
        queue->heap_for_huffman[index - 1] = temp;
        index--;
    }
}


QUEUE* Creating_queue(QUEUE * queue){
    queue = (QUEUE*) malloc(sizeof(QUEUE));
    queue->size = 0;
    queue->heap_for_huffman = NULL;
    return queue;
}


void reading_file(FILE * input) {
    wchar_t symbol;
    QUEUE *priority_queue = NULL;
    priority_queue = Creating_queue(priority_queue);

    while ((symbol = fgetwc(input)) != WEOF) {
        int check_in_queue = 0;
        for (int i = 0; i < priority_queue->size; i++){
            if (priority_queue->heap_for_huffman[i]->symbol == symbol) {
                priority_queue->heap_for_huffman[i]->freq++;
                check_in_queue = 1;

                while (i > 0 && priority_queue->heap_for_huffman[i]
                ->freq < priority_queue->heap_for_huffman[i - 1]->freq){
                    NODE *temp = priority_queue->heap_for_huffman[i];
                    priority_queue->heap_for_huffman[i] = priority_queue
                            ->heap_for_huffman[i - 1];
                    priority_queue->heap_for_huffman[i - 1] = temp;
                }
                check_in_queue = 1;
                break;
            }
        }
        if (!check_in_queue) {
            update_size(priority_queue);
            add_node(symbol, priority_queue);
        }
    }
    printf("%d", priority_queue->size);
    print_queue(priority_queue);
}


int main(){
    setlocale(LC_ALL, "");
    FILE * input = fopen("input.txt", "r, ccs=UTF-8");
    FILE * output = fopen("output.txt", "w, ccs=UTF-8");
    reading_file(input);




    return 0;
}
