#include "Prim_function.h"
#include <stdio.h>
#include <stdlib.h>

GRAPH * Create_graph(GRAPH * graph, int node_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> adj_matrix = (int *)malloc(node_count * node_count * sizeof(int));


    for (int i = 0; i < node_count * node_count; i++)
        graph -> adj_matrix[i] = 0;


    return graph;
}


void add_edge(int start, int finish, int weight, GRAPH * graph){
    graph -> adj_matrix[start * graph -> node_count + finish] = weight;
    graph -> adj_matrix[finish * graph -> node_count + start] = weight;
}


int min_key(int * visited, unsigned int * keys, int node_count){
    unsigned int min_key = UINT_MAX;
    int min_index;
    for (int i = 0; i < node_count; i++)
        if ( visited[i] == 0 &&  keys[i] < min_key){
            min_key =  keys[i];
            min_index = i;
        }

    return min_index;
}


void print_Prim(int * parents, int node_count){
    for (int i = 1; i < node_count; i++)
        printf("%d %d\n", parents[i] + 1, i + 1);

}

void free_graph(GRAPH * graph){
    free(graph -> adj_matrix);
    free(graph);
}


void Prim_alg(GRAPH * graph){
    int node_count = graph -> node_count;
    int * visited;
    int * parents;
    unsigned int * keys;
    visited = malloc(node_count * sizeof(int));
    keys = malloc(node_count * sizeof(unsigned int));
    for (int i = 0; i < node_count; i++) {
        visited[i] = 0;
        keys[i] = UINT_MAX;
    }
    parents = (int*) malloc(node_count * sizeof(int));

    keys[0] = 0;
    parents[0] = -1;

    for (int i = 0; i < node_count - 1; i++){
        int visit = min_key(visited ,keys, node_count);

        visited[visit] = 1;
        for (int j = 0; j < node_count; j++)
            if (graph -> adj_matrix[visit * node_count + j]
                && visited[j] == 0 &&
                graph -> adj_matrix[visit * node_count + j] < keys[j]){
                parents[j] = visit;
                keys[j] = graph->adj_matrix[visit * node_count + j];
            }

    }
    for (int i = 0; i < node_count; i++)
        if (keys[i] == UINT_MAX) {
            puts("no spanning tree");
            return;
        }

    print_Prim(parents, node_count);
    free_graph(graph);
}
