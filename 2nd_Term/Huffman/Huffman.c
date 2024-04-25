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

void sort_queue(QUEUE * queue, int index){
    while (index > 0 && queue->heap_for_huffman[index]->freq >
    queue->heap_for_huffman[index-1]->freq){
        NODE * temp = queue->heap_for_huffman[index];
        queue->heap_for_huffman[index] = queue->heap_for_huffman[index-1];
        queue->heap_for_huffman[index-1] = temp;
        index--;
    }
}


void update_size(QUEUE * queue, int size){
    queue->heap_for_huffman = realloc(queue->heap_for_huffman,
                                      size * sizeof(NODE*));
    queue->size = size;
}


NODE * Creating_node(NODE * node, wchar_t symbol, int long freq){
    node = (NODE*) malloc(sizeof(NODE));
    node -> symbol = symbol;
    node -> freq = freq;
    node->left = NULL;
    node->right = NULL;
    return  node;
}


NODE * Creating_tree(QUEUE * queue){
    int index = queue->size-1;
    while (index > 0){
        NODE * connection = NULL;
        connection = Creating_node(connection, WEOF,
                                   queue->heap_for_huffman[index]->freq +
                                   queue->heap_for_huffman[index-1]->freq);
        connection -> left = queue->heap_for_huffman[index-1];
        connection -> right = queue->heap_for_huffman[index];

        queue->heap_for_huffman[--index] = connection;
        printf("%ld\n", queue->heap_for_huffman[index]->freq);
        update_size(queue, queue->size-1);
        printf("%ld\n", queue->heap_for_huffman[index]->freq);
        sort_queue(queue, index);
    }
    return queue->heap_for_huffman[0];
}



void add_node(wchar_t symbol, QUEUE * queue){
    NODE * new_node = NULL;
    new_node = Creating_node(new_node, symbol, 1);

    update_size(queue, queue->size + 1);

    int index = queue->size - 1;
    queue->heap_for_huffman[index] = new_node;

    while (index > 0 && queue->heap_for_huffman[index]->freq
    >= queue->heap_for_huffman[index-1]->freq){
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

void making_codes(NODE * tree){

}


void reading_file(FILE * input, FILE * output) {
    wchar_t symbol;
    QUEUE *priority_queue = NULL;
    priority_queue = Creating_queue(priority_queue);

    while ((symbol = fgetwc(input)) != WEOF) {
        int check_in_queue = 0;
        for (int i = 0; i < priority_queue->size; i++){
            if (priority_queue->heap_for_huffman[i]->symbol == symbol) {
                priority_queue->heap_for_huffman[i]->freq++;

                while (i > 0 && priority_queue->heap_for_huffman[i]
                ->freq > priority_queue->heap_for_huffman[i - 1]->freq){
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
            add_node(symbol, priority_queue);
        }
    }
    NODE * huffman_tree = NULL;
    huffman_tree = Creating_tree(priority_queue);
    makind_codes(huffman_tree);

}


int main(){
    setlocale(LC_ALL, "");
    FILE * input = fopen("input.txt", "r, ccs=UTF-8");
    FILE * output = fopen("output.txt", "w, ccs=UTF-8");
    reading_file(input, output);




    return 0;
}
