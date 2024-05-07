#include "Kosaraju_func.h"
#include <stdio.h>
#include <stdlib.h>


GRAPH * Create_graph(GRAPH * graph, int node_count){
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> adj_matrix = calloc(node_count * node_count, sizeof(char));
    graph -> rev_adj_matrix = calloc(node_count * node_count, sizeof(char));


    return graph;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[(st_edge-1) * graph -> node_count + (fn_edge-1)] = 1;
    graph -> rev_adj_matrix[(fn_edge-1) * graph -> node_count + (st_edge-1)] = 1;
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
        if (graph->adj_matrix[cur * graph->node_count + i])
            if (!visited[i])
                dfs(graph, i, visited, stack);


    push_stack(stack, cur);
}


void dfs_for_result(GRAPH * graph, int * visited, int cur, int colour){
    int node_count = graph -> node_count;
    visited[cur] = colour;
    for (int i = 0; i < node_count; i++)
        if (graph->rev_adj_matrix[cur * node_count + i] && !visited[i])
            dfs_for_result(graph, visited, i, colour);
}


int max(int * visited, int node_count){
    int max = -INT_MAX;
    for (int i = 0; i < node_count; i++)
        if (visited[i] > max)
            max = visited[i];
    return max;
}


void print_res(int * visited, int node_count){
    int max_component = max(visited, node_count);
    for (int i = 1; i < max_component + 1; i++){
        printf("SCC #%d\n", i);
        for (int j = 0; j < node_count; j++){
            if (visited[j] == i)
                printf("%d ", j + 1);
        }
        puts("\n");
    }
}


void find_SCC(GRAPH * graph, STACK * stack, int * visited){
    int colour = 0;
    while (stack -> top != -1){
        int cur = pop_stack(stack);
        printf("%d", cur + 1);
        if (!visited[cur])
            dfs_for_result(graph, visited, cur, ++colour);

    }

    print_res(visited, graph -> node_count);
}


void free_all(GRAPH * graph, STACK * stack, int * arr){
    free(graph ->adj_matrix);
    free(graph -> rev_adj_matrix);
    free(graph);
    free(stack->data);
    free(stack);
    free(arr);
}


void Kosaraju(GRAPH * graph){
    int node_count = graph -> node_count;

    STACK * stack = (STACK *) malloc(sizeof(STACK));
    Create_stack(stack, node_count);
    int * visited;
    visited = calloc(node_count, sizeof(int));

    for (int i = 0; i < node_count; i++){
        if (!visited[i])
            dfs(graph, i, visited , stack);
    }


    for (int i = 0; i < node_count; i++)
        visited[i] = 0;

    find_SCC(graph, stack, visited);

    free_all(graph, stack, visited);
}