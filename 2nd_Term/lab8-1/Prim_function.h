
#ifndef NSU_LEARNING_PRIM_FUNCTION_H
#define NSU_LEARNING_PRIM_FUNCTION_H

#define GRAPH struct graph

GRAPH{
    int node_count;
    int * adj_matrix;
    int * visited;
    int * parents;
    unsigned int * keys;
};

GRAPH * Create_graph(GRAPH * graph, int node_count);
void add_edge(int start, int finish, int weight, GRAPH * graph);
int min_key(GRAPH * graph);
void print_Prim(GRAPH * graph);
void free_graph(GRAPH * graph);
void Prim_alg(GRAPH * graph);

#endif
