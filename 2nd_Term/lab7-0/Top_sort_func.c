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


void Create_stack(STACK * stack, int node_count){
    stack -> data = (int *)malloc(node_count * sizeof(int));
    stack -> top = -1;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[st_edge * graph -> node_count + fn_edge] = 1;
}


void push_stack(STACK * stack, int cur){
    stack -> data[++stack-> top] = cur;
}

void dfs(GRAPH* graph, int cur, int* visited, STACK * stack) {
    visited[cur] = 1;
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->adj_matrix[cur * graph->node_count + i] && !visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }

    push_stack(stack, cur + 1);

}


void Top_Sort(GRAPH * graph){
    int node_count = graph -> node_count;
    int * visited;
    STACK * stack = (STACK *) malloc(sizeof(STACK));
    visited = calloc(node_count, sizeof(int));
    Create_stack(stack, node_count);


    for (int i = 0; i < node_count; i++){
        if (!visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }

    while (stack -> top != -1){
        printf("%d ", stack->data[stack->top]);
        stack -> top --;
    }


    free(visited);


}

