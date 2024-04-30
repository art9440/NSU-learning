#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uchar.h>
#include <locale.h>


#define QUEUE struct queue
#define NODE struct node
#define CODE struct code
#define BITSTREAM struct bitstream

CODE{
    unsigned int symbol;
    unsigned int code;
};

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


BITSTREAM{
    FILE  * file;
    long data;
    int position;
};

BITSTREAM * Creating_bitstream(BITSTREAM * stream){
    stream = malloc(sizeof(BITSTREAM));
    stream->file=
}

void tree_to_file(NODE * tree){

}

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
    while (queue->size > 1) {
        NODE* connection = Creating_node(NULL, WEOF,
                                         queue->heap_for_huffman[queue->size - 1]->freq +
                                         queue->heap_for_huffman[queue->size - 2]->freq);
        connection->left = queue->heap_for_huffman[queue->size - 2];
        connection->right = queue->heap_for_huffman[queue->size - 1];

        update_size(queue, queue->size - 1);
        queue->heap_for_huffman[queue->size - 1] = connection;

        sort_queue(queue, queue->size - 1);
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


void making_codes(NODE * tree, CODE * codes, int * index, unsigned int code){
    if (tree->left == NULL && tree->right == NULL){
        codes[*index].symbol = tree->symbol;
        codes[(*index)++].code = code;
        return;
    }
    making_codes(tree->left, codes, index, code << 1);
    making_codes(tree->right, codes, index, (code << 1) | 1);
}


void print_codes(CODE * codes, int  code_len){
    FILE  * output = fopen("output.txt", "w");
    for (int i = 0; i < code_len; i++){
        fprintf(output, "%d --  %d ", codes[i].symbol, codes[i].code);
    }
    fclose(output);
}

void print_tree(NODE * tree){
    printf("%lc -- %d\n", tree->symbol, tree->freq);
    if (tree->left != NULL)
        print_tree(tree->left);
    if (tree->right != NULL)
        print_tree(tree->right);
    return;
}

void print_queue(QUEUE * queue){
    for (int i = 0; i < queue->size; i++){
        printf("%c %d#\n", queue->heap_for_huffman[i]->symbol, queue->heap_for_huffman[i]->freq);
    }
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

                while (i > 0 && priority_queue->heap_for_huffman[i]
                ->freq > priority_queue->heap_for_huffman[i - 1]->freq){
                    NODE *temp = priority_queue->heap_for_huffman[i];
                    priority_queue->heap_for_huffman[i] = priority_queue
                            ->heap_for_huffman[i - 1];
                    priority_queue->heap_for_huffman[i - 1] = temp;
                    i--;
                }
                check_in_queue = 1;
                break;
            }
        }
        if (!check_in_queue) {
            add_node(symbol, priority_queue);
        }
    }
    //print_queue(priority_queue);
    NODE * huffman_tree = NULL;
    huffman_tree = Creating_tree(priority_queue);
    //print_tree(huffman_tree);
    CODE * all_codes = NULL;
    all_codes = (CODE*)malloc(priority_queue->size * sizeof(CODE));
    int all_codes_len = 0;
    making_codes(huffman_tree, all_codes, &all_codes_len, 0);
    BITSTREAM * stream = NULL;
    stream = Creating_bitstream(stream);
    tree_to_file(huffman_tree);
    //print_codes(all_codes, all_codes_len);
}


int main(){
    setlocale(LC_ALL, "");
    FILE * input = fopen("input.txt", "r, ccs=UTF-8");
    reading_file(input);
    fclose(input);
    return 0;
}
