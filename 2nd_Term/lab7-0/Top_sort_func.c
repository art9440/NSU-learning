#include "Top_sort_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

GRAPH * Create_graph(GRAPH * graph, int node_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> check_res = 0;
    graph -> adj_matrix = (int *)malloc(node_count * node_count * sizeof(int));

    for (int i = 0; i < node_count * node_count; i++)
        graph -> adj_matrix[i] = 0;


    return graph;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge){
    graph -> adj_matrix[st_edge * graph -> node_count + fn_edge] = 1;
}


void dfs(GRAPH * graph, int cur, int * visited, int * stack){
    visited[cur] = 1;
    for (int i = 0; i < graph -> node_count; i++){
        if (graph -> adj_matrix[cur * graph -> node_count + i] && !visited[i])
            dfs(graph, i, visited, stack);
    }

    *stack = *stack + 1;
    stack[*stack] = cur;
    graph -> check_res ++;
}


void Top_Sort(GRAPH * graph){
    int node_count = graph -> node_count;
    int * visited;
    int * stack;
    visited = calloc(node_count, sizeof(int));
    stack = malloc(node_count * sizeof(int));

    for (int i = 0; i < node_count; i++){
        if (!visited[i])
            dfs(graph, i, visited, stack);
    }

    if (graph -> check_res != node_count){
        puts("impossible to sort");
        return;
    }


    int res = node_count;
    while (res != -1){
        printf("%d", stack[res]);
        res--;
    }
    free(stack);
    free(visited);


}

