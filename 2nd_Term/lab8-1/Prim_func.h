#ifndef NSU_LEARNING_PRIM_FUNC_H
#define NSU_LEARNING_PRIM_FUNC_H

#define GRAPH struct graph

GRAPH{
    int node_count;
    int edge_count;
    int * adj_matrix;
    int * visited;
};

int min(int a, int b){
    if (a < b)
        return a;
    return b;
}


GRAPH * Create_graph(GRAPH * graph, int node_count, int edge_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> node_count = node_count;
    graph -> edge_count = edge_count;
    graph -> adj_matrix = (int *)malloc(node_count * node_count * sizeof(int));
    graph -> visited = (int*) malloc(node_count * sizeof(int));

    for (int i = 0; i < node_count * node_count; i++)
        graph -> adj_matrix[i] = 0;
    for (int i = 0; i < node_count; i++)
        graph -> visited[i] = 0;

    return graph;
}


void add_edge(int start, int finish, int weight, GRAPH * graph){
    graph -> adj_matrix[start * graph -> node_count + finish] = weight;
    graph -> adj_matrix[finish * graph -> node_count + start] = weight;
}


void Prim_alg(GRAPH * graph, int start_node){
    graph -> visited[start_node] = 1;
    int node_count = graph -> node_count;
    int edge_count = graph -> edge_count;
    int min_weight = INT_MAX;
    for(int i = start_node * node_count; i < (start_node + 1) * node_count; i++){
        if (graph -> adj_matrix[start_node * node_count + i] != 0)
            min_weight = min(min_weight, graph -> adj_matrix[start_node * node_count + i]);
    }
}
#endif
