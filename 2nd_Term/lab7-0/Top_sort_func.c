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


void Create_stack(STACK * stack, int node_count){
    stack -> data = (int *)malloc(node_count * sizeof(int));
    stack -> top = -1;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[(st_edge-1) * graph -> node_count + (fn_edge-1)] = 1;
}


void push_stack(STACK * stack, int cur){
    stack -> data[++stack-> top] = cur;
}

void dfs(GRAPH* graph, int cur, int* visited, STACK * stack, int* cycle_detect) {
    visited[cur] = 1;
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->adj_matrix[cur * graph->node_count + i]) {
            if (visited[i] == 1) {
                *cycle_detect = 1;
                return;
            }
            else if (!visited[i]) {
                dfs(graph, i, visited, stack, cycle_detect);
            }
        }
    }

    push_stack(stack, cur + 1);
    visited[cur] = 2;
}

void free_all(int * visited, STACK * stack, GRAPH * graph){
    free(visited);
    free(graph->adj_matrix);
    free(stack->data);
    free(graph);
    free(stack);
}

void Top_Sort(GRAPH * graph){
    int node_count = graph -> node_count;
    int * visited;
    STACK * stack = (STACK *) malloc(sizeof(STACK));
    visited = calloc(node_count, sizeof(int));
    Create_stack(stack, node_count);

    int cycle_detect = 0;

    for (int i = 0; i < node_count; i++){
        if (!visited[i]) {
            dfs(graph, i, visited, stack, &cycle_detect);
            if (cycle_detect) {
                break;
            }
        }
    }

    if (cycle_detect) {
        printf("impossible to sort\n");
        free_all(visited, stack, graph);
        return;
    } else {
        while (stack -> top != -1){
            printf("%d ", stack->data[stack->top]);
            stack -> top --;
        }
    }

    free_all(visited, stack, graph);
}
