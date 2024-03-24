#ifndef NSU_LEARNING_PRIM_FUNC_H
#define NSU_LEARNING_PRIM_FUNC_H

#define GRAPH struct graph

GRAPH{
    int node_count;
    int * adj_matrix;
    int * visited;
    int * parents;
    unsigned int * keys;
};


GRAPH * Create_graph(GRAPH * graph, int node_count, int edge_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> adj_matrix = (int *)malloc(node_count * node_count * sizeof(int));
    graph -> visited = (int*) malloc(node_count * sizeof(int));
    graph -> parents = (int*) malloc(node_count * sizeof(int));
    graph -> keys = malloc(node_count * sizeof(unsigned int));

    for (int i = 0; i < node_count * node_count; i++)
        graph -> adj_matrix[i] = 0;

    for (int i = 0; i < node_count; i++) {
        graph->visited[i] = 0;
        graph -> keys[i] = UINT_MAX;
    }

    graph -> keys[0] = 0;
    graph -> parents[0] = -1;

    return graph;
}


void add_edge(int start, int finish, int weight, GRAPH * graph){
    graph -> adj_matrix[start * graph -> node_count + finish] = weight;
    graph -> adj_matrix[finish * graph -> node_count + start] = weight;
}


int min_key(GRAPH * graph){
    unsigned int min_key = UINT_MAX;
    int min_index;
    for (int i = 0; i < graph -> node_count; i++)
        if (graph -> visited[i] == 0 && graph -> keys[i] < min_key){
            min_key = graph -> keys[i];
            min_index = i;
        }

    return min_index;
}


void print_Prim(GRAPH * graph){
    for (int i = 1; i < graph -> node_count; i++)
        printf("%d %d\n", graph -> parents[i] + 1, i + 1);

}

void free_graph(GRAPH * graph){
    free(graph -> adj_matrix);
    free(graph -> visited);
    free(graph -> keys);
    free(graph -> parents);
    free(graph);
}


void Prim_alg(GRAPH * graph){
    int node_count = graph -> node_count;

    for (int i = 0; i < node_count - 1; i++){
        int visit = min_key(graph);

        graph -> visited[visit] = 1;
        for (int j = 0; j < node_count; j++)
            if (graph -> adj_matrix[visit * node_count + j]
            && graph -> visited[j] == 0 &&
            graph -> adj_matrix[visit * node_count + j] < graph -> keys[j]) {
                graph->parents[j] = visit;
                graph->keys[j] = graph->adj_matrix[visit * node_count + j];
            }

    }
    for (int i = 0; i < node_count; i++)
        if (graph -> keys[i] == UINT_MAX) {
            puts("no spanning tree");
            return;
        }

    print_Prim(graph);
    free_graph(graph);
}
#endif
