#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>


#define QUEUE struct queue
#define NODE struct node
#define CODE struct code
#define BITSTREAM struct bitstream
#define ERRORS enum errors

#define BUFFER 8
#define OCTET 32

CODE{
    unsigned int symbol;
    unsigned int code;
    int len;
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

ERRORS{
    non_error,
    error
};






int last_child(NODE * tree){
    return  !tree->left;
}


void write_bit(BITSTREAM * stream, int  bit){
    if (stream->position == BUFFER){
        fwrite(&(stream->data), sizeof(char), 1, stream->file);
        stream->position = 0;
        stream->data = 0;
    }
    stream -> data = bit | (stream->data << 1);
    stream->position++;
}

void write_symbol(BITSTREAM * stream, wchar_t  symbol){
    for (int i = OCTET - 1; i >= 0; i--){
        int bit = (symbol >> i) & 1;
        write_bit(stream, bit);
    }
}


BITSTREAM * Creating_bitstream( FILE * file){
    BITSTREAM * stream = malloc(sizeof(BITSTREAM));
    stream->file= file;
    stream -> data = 0;
    stream -> position = 0;
    return stream;
}

void tree_to_file(NODE * tree, BITSTREAM * stream){
    if (last_child(tree)){
        write_bit(stream, 1);
        //printf("1");
        //printf("%c", tree->symbol);
        write_symbol(stream, tree->symbol);
        return;
    }
    write_bit(stream, 0);
    tree_to_file(tree->left, stream);
    tree_to_file(tree->right, stream);
}


void update_size(QUEUE * queue, int size){
    queue->heap_for_huffman = realloc(queue->heap_for_huffman,
                                      size * sizeof(NODE*));
    queue->size = size;
}


NODE * Creating_node(wchar_t symbol, int long freq, NODE * left, NODE * right){
    NODE * node = (NODE*) malloc(sizeof(NODE));
    node -> symbol = symbol;
    node -> freq = freq;
    node->left = left;
    node->right = right;
    return  node;
}

void add_node(NODE * new_node, QUEUE * queue){
    update_size(queue, queue->size+1);
    int index = queue->size - 1;
    while (index > 0 && new_node->freq >= queue->heap_for_huffman[index-1]->freq){
        queue->heap_for_huffman[index] = queue->heap_for_huffman[index-1];
        index--;
    }
    queue->heap_for_huffman[index] = new_node;
}


NODE * Creating_tree(QUEUE * queue){
    while (queue->size > 1){
        NODE * left_node = queue->heap_for_huffman[--queue->size];
        NODE * right_node = queue->heap_for_huffman[--queue->size];
        NODE * connection = Creating_node( 0, left_node->freq +
        right_node->freq, left_node, right_node);
        add_node(connection, queue);
    }
    return queue->heap_for_huffman[0];

}


QUEUE* Creating_queue(){
    QUEUE * queue = (QUEUE*) malloc(sizeof(QUEUE));
    queue->size = 0;
    queue->heap_for_huffman = NULL;
    return queue;
}


void making_codes(NODE * tree, CODE * codes, int * index, unsigned int code, int len){
    if (tree->left == NULL ){
        //puts("$");
        codes[*index].symbol = tree->symbol;
        codes[*index].len = len;
        codes[(*index)++].code = code;
        return;
    }
    making_codes(tree->left, codes, index, code << 1, len + 1);
    making_codes(tree->right, codes, index, (code << 1) | 1, len + 1);
}


void print_codes(CODE * codes, int  code_len){
    FILE  * output = fopen("output.txt", "w");
    for (int i = 0; i < code_len; i++){
        fprintf(output, "%d --  %d ", codes[i].symbol, codes[i].code);
    }
    fclose(output);
}

void print_tree(NODE * tree){
    printf("%d -- %d\n", tree->symbol, tree->freq);
    if (tree->left != NULL)
        print_tree(tree->left);
    if (tree->right != NULL)
        print_tree(tree->right);
}

void print_queue(QUEUE * queue){
    for (int i = 0; i < queue->size; i++){
        printf("%c %ld#\n", queue->heap_for_huffman[i]->symbol, queue->heap_for_huffman[i]->freq);
    }
}

void coding_text(wchar_t symbol, BITSTREAM * stream, CODE * codes, int codes_len){
    int i;
    for (i = 0; i < codes_len; i++){
        if(codes[i].symbol == symbol)
            break;
    }
    for (int j = codes[i].len - 1; j >= 0; j--){
        int bit = (codes[i].code >> j) & 1;
        //printf("%d==\n", bit);
        write_bit(stream, bit);
    }
}

void To_queue(QUEUE * queue, FILE * input){
    wchar_t symbol;
    while ((symbol = fgetwc(input)) != WEOF) {
        //printf(" %d ", symbol);
        int check_in_queue = 0;
        for (int i = 0; i < queue->size; i++){
            if (queue->heap_for_huffman[i]->symbol == symbol) {
                queue->heap_for_huffman[i]->freq++;

                while (i > 0 && queue->heap_for_huffman[i]
                                        ->freq >= queue->heap_for_huffman[i - 1]->freq){
                    NODE *temp = queue->heap_for_huffman[i];
                    queue->heap_for_huffman[i] = queue
                            ->heap_for_huffman[i - 1];
                    queue->heap_for_huffman[i - 1] = temp;
                    i--;
                }
                check_in_queue = 1;
                break;
            }
        }
        if (!check_in_queue) {
            add_node(Creating_node(symbol, 1, NULL, NULL), queue);
        }
    }
    rewind(input);
}


void encode(FILE * input, FILE * output) {
    wchar_t symbol;

    BITSTREAM * stream = Creating_bitstream(output);

    QUEUE * priority_queue = Creating_queue();
    To_queue(priority_queue, input);
    //printf("%d[[[[[[\n", priority_queue->size);

    CODE * all_codes = (CODE*)malloc(priority_queue->size * sizeof(CODE));


    NODE * huffman_tree = Creating_tree(priority_queue);
    //print_tree(huffman_tree);
    //puts("#---------");
    //printf("%d---------", priority_queue->size);
    int all_codes_len = 0;

    making_codes(huffman_tree, all_codes, &all_codes_len, 0, 0);
    //for (int i = 0; i < all_codes_len; i++){
        //printf("%lc -- %d\n", all_codes[i].symbol, all_codes[i].code);
    //}

    //puts("*");


    fwrite(&(huffman_tree->freq), sizeof(int), 1, stream->file);
    tree_to_file(huffman_tree, stream);

    fseek(input, 0, SEEK_END);
    long count_byte = ftell(input);
    rewind(input);

    for (int i = 0; i < count_byte / sizeof(wchar_t); i++){
        symbol = fgetwc(input);
        coding_text(symbol, stream, all_codes, all_codes_len);
    }

    stream->data = stream->data << (BUFFER - stream->position);
    fwrite(&(stream->data), sizeof(char), 1, stream->file);
    free(priority_queue);
    free(all_codes);
    free(huffman_tree);
    free(stream);
}

ERRORS read_bit(int  *bit, BITSTREAM * stream){
    if (stream->position == 0) {
        if (fread(&(stream->data), sizeof(char), 1, stream->file) != 1)
            return error;
        stream->position = BUFFER;
    }

    stream->position--;
    *bit = (stream->data >> stream->position) & 1;
    return non_error;
}

ERRORS read_symbol(wchar_t * symbol, BITSTREAM * stream){
    *symbol = 0;
    for (int i = 0; i < OCTET; i++){
        *symbol = *symbol << 1;
        int bit;

        if(read_bit(&bit, stream) == error)
            return error;
        *symbol = *symbol | bit;
    }
    return non_error;
}


NODE * Get_Tree(BITSTREAM * stream){
    int bit;
    if(read_bit(&bit, stream) == error)
        return NULL;
    if (bit == 1){
        wchar_t symbol;
        if(read_symbol(&symbol, stream) == error)
            return NULL;
        return Creating_node(symbol, 0, NULL, NULL);
    }
    NODE * left_node = Get_Tree(stream);
    NODE * right_node = Get_Tree(stream);
    return Creating_node(0, 0, left_node, right_node);
}

void Get_symbol(wchar_t * symbol, BITSTREAM * stream, NODE * tree){
    NODE * cur = tree;
    while (!last_child(cur)){
        int bit;
        read_bit(&bit, stream);
        if (bit == 0)
            cur = cur->left;
        else
            cur = cur->right;
    }
    *symbol = cur->symbol;
}

void free_tree(NODE * tree){
    if (tree == NULL)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}



void decode(FILE * input, FILE * output){
    BITSTREAM * stream = Creating_bitstream(input);
    int len;
    fread(&len, sizeof(long), 1, stream->file);
    //printf("%d", len);
    //puts("*");
    NODE * tree = Get_Tree(stream);
    //puts("#");
    print_tree(tree);

    for (int i = 0; i < len; i++){
        wchar_t symbol;
        Get_symbol(&symbol, stream, tree);
        fwrite(&symbol, sizeof(wchar_t), 1, output);
    }
    free_tree(tree);
    free(stream);
}


int main(int argc, char * argv[]){
    setlocale(LC_ALL, "");

    char * action = argv[1];
    char * input_file = argv[2];
    char * output_file = argv[3];

    if (strcmp(action, "c") == 0) {
        FILE * input = fopen(input_file, "rb");
        FILE * output = fopen(output_file, "wb");
        encode(input, output);
        fclose(input);
        fclose(output);
    }
    else if (strcmp(action, "d") == 0)
    {
        FILE * input = fopen(input_file, "rb");
        FILE * output = fopen(output_file, "wb");
        decode(input, output);
        fclose(input);
        fclose(output);
    }

    return 0;
}