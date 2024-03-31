
#ifndef NSU_LEARNING_PRIM_FUNCTION_H
#define NSU_LEARNING_PRIM_FUNCTION_H

#define GRAPH struct graph

GRAPH{
    int node_count;
    int * adj_matrix;
};

GRAPH * Create_graph(GRAPH * graph, int node_count);
void add_edge(int start, int finish, int weight, GRAPH * graph);
int min_key(int * visited, unsigned int * keys, int node_count);
void print_Prim(int * parents, int node_count);
void free_graph(GRAPH * graph);
void Prim_alg(GRAPH * graph);

#endif
