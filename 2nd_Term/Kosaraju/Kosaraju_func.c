#include "Kosaraju_func.h"
#include <stdio.h>
#include <stdlib.h>


GRAPH * Create_graph(GRAPH * graph, int node_count){
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> adj_matrix = calloc(node_count * node_count, sizeof(char));


    return graph;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[(st_edge-1) * graph -> node_count + (fn_edge-1)] = 1;
}


void Create_stack(STACK * stack, int node_count){
    stack -> data = (int *)malloc(node_count * sizeof(int));
    stack -> top = -1;
}


void push_stack(STACK * stack, int cur){
    stack -> data[++stack-> top] = cur;
}


int pop_stack(STACK * stack){
    return stack->data[stack->top--];
}


void dfs(GRAPH* graph, int cur, int* visited, STACK * stack) {
    visited[cur] = 1;
    for (int i = 0; i < graph->node_count; i++)
        if (graph->adj_matrix[cur * graph->node_count + i]) {
            if (!visited[i])
                dfs(graph, i, visited, stack);
        }

    push_stack(stack, cur + 1);
}


void dfs_for_result(GRAPH * graph, int * visited, int * deleted, int cur){
    int node_count = graph -> node_count;
    printf("%d", cur);
    visited[cur] = 1;
    deleted[cur] = 1;
    for (int i = 0; i < node_count; i++)
        if (graph->adj_matrix[cur * node_count + i])
            if (!visited[i] && !deleted[i])
                dfs_for_result(graph, visited, deleted, i);
}


void find_SCC(GRAPH * graph, STACK * stack, int * visited){
    int node_count = graph -> node_count;
    int * deleted = calloc(node_count, sizeof(int));
    int count = 1;
    while (stack->top!= -1){
        int cur = pop_stack(stack);
        if (cur && !deleted[cur]){
            for (int i = 0; i < node_count; i++)
                visited[i] = 0;
            printf("SCC №%d", count);
            dfs_for_result(graph, visited, deleted, cur);
            puts("\n");
            count++;
        }
    }

    free(deleted);
}


GRAPH * reverse(GRAPH * graph){
    int node_count = graph -> node_count;
    GRAPH * reversed_graph = NULL;
    reversed_graph = Create_graph(reversed_graph, node_count);

    for (int i = 0; i < node_count;i++)
        for (int j = 0; j < node_count; j++)
            if (graph->adj_matrix[i * node_count + j])
                reversed_graph->adj_matrix[j * node_count + i] = 1;

    return reversed_graph;
}


void free_all(GRAPH * graph, GRAPH * rev_graph, STACK * stack, int * arr){
    free(graph ->adj_matrix);
    free(graph);
    free(rev_graph->adj_matrix);
    free(rev_graph);
    free(stack->data);
    free(stack);
    free(arr);
}


void Kosaraju(GRAPH * graph){
    int node_count = graph -> node_count;
    STACK * stack = NULL;
    Create_stack(stack, node_count);
    int * visited;
    visited = calloc(node_count, sizeof(int));

    for (int i = 0; i < node_count; i++){
        if (!visited[i])
            dfs(graph, i, visited , stack);
    }

    GRAPH * reversed_graph = reverse(graph);

    find_SCC(reversed_graph, stack, visited);

    free_all(graph, reversed_graph, stack, visited);
}