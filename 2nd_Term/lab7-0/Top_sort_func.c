#include "Top_sort_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

GRAPH * Create_graph(GRAPH * graph, int node_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> adj_matrix = malloc(node_count * node_count * sizeof(int));

    for (int i = 0; i < node_count * node_count; i++)
        graph -> adj_matrix[i] = 0;


    return graph;
}

STACK * Create_node_stack(int cur){
    STACK * newNode = (STACK*) malloc(sizeof(STACK));
    newNode -> vertex = cur;
    newNode -> next = NULL;
    return  newNode;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[st_edge * graph -> node_count + fn_edge] = 1;
}


void dfs(GRAPH* graph, int cur, int* visited, STACK ** stack) {
    visited[cur] = 1;
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->adj_matrix[cur * graph->node_count + i] && !visited[i]) {
            printf("*%d ", cur);
            dfs(graph, i, visited, stack);
        }
    }
    STACK * newNode = Create_node_stack(cur);
    newNode -> next = *stack;
    *stack = newNode;

}


void Top_Sort(GRAPH * graph){
    int node_count = graph -> node_count;
    int * visited;
    STACK * stack = NULL;
    visited = calloc(node_count, sizeof(int));


    for (int i = 0; i < node_count; i++){
        if (!visited[i]) {
            dfs(graph, i, visited, &stack);
        }
    }

    while (stack != NULL) {
        printf("%d ", stack->vertex);
        STACK * temp = stack;
        stack = stack->next;
        free(temp);
    }

    free(visited);


}

