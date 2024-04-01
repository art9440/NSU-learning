#include "Top_sort_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

GRAPH * Create_graph(GRAPH * graph, int node_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> adj_matrix = malloc(node_count * node_count * sizeof(char));

    for (int i = 0; i < node_count * node_count; i++)
        graph -> adj_matrix[i] = 0;

    return graph;
}

void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[(st_edge-1) * graph -> node_count + (fn_edge-1)] = 1;
}

void Create_queue(QUEUE ** queue, int node_count){
    *queue = (QUEUE*) malloc(sizeof(QUEUE));
    (*queue) -> qu = malloc(node_count * sizeof(int));
    (*queue) -> front = -1;
    (*queue) -> rear = -1;
}

void Enqueue(QUEUE * queue, int cur){
    if (queue -> front == -1)
        queue -> front = 0;
    queue -> rear++;
    queue->qu[queue->rear] = cur;
}

int isEmpty(QUEUE * queue){
    if (queue -> rear == -1)
        return 1;
    return 0;
}

int Dequeue(QUEUE * queue){
    int num;
    if (isEmpty(queue))
        num = -1;
    else{
        num = queue -> qu[queue->front];
        queue->front++;
        if (queue -> front > queue -> rear) {
            queue->front = -1;
            queue->rear = -1;
        }
    }
    return num;
}

void free_all(GRAPH * graph, QUEUE * q){
    free(graph -> adj_matrix);
    free(graph);
    free(q->qu);
    free(q);
}

void Top_Sort(GRAPH * graph) {
    int node_count = graph->node_count;
    int * indegree = calloc(node_count, sizeof(int));
    int * res =  malloc(node_count * sizeof(int));
    for (int i = 0; i < node_count; i++)
        for (int j = 0; j < node_count; j++)
            if (graph -> adj_matrix[i * node_count + j] != 0)
                indegree[j]++;


    QUEUE *queue = NULL;
    for (int i = 0; i< node_count; i++)
    Create_queue(&queue, node_count);
    for (int i = 0;i < node_count; i++){
        if (indegree[i] == 0) {
            Enqueue(queue, i);
        }
    }

    int index = 0;
    while (!isEmpty(queue)){
        int cur = Dequeue(queue);
        res[index++] = cur + 1;

        for (int i = 0; i < node_count; i++){
            if (graph -> adj_matrix[cur * node_count + i] == 1){
                indegree[i]--;
                if (indegree[i] == 0)
                    Enqueue(queue, i);
            }
        }
    }
    if (index != node_count){
        puts("impossible to sort");
        free_all(graph, queue);
        free(indegree);
        return;
    }

    for (int i = 0; i < node_count; i++)
        printf("%d ", res[i]);
    free_all(graph, queue);
    free(indegree);
}
