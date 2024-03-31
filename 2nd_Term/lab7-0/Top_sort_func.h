#ifndef NSU_LEARNING_TOP_SORT_FUNC_H
#define NSU_LEARNING_TOP_SORT_FUNC_H

#define GRAPH struct graph
#define STACK struct stack

GRAPH{
    int node_count;
    int * adj_matrix;
};

STACK{
    int vertex;
    STACK * next;
};



GRAPH * Create_graph(GRAPH * graph, int node_count);
void add_edge(GRAPH * graph, int st_edge, int fn_edge);
void Top_Sort(GRAPH * graph);
void dfs(GRAPH * graph, int cur, int * visited, STACK ** stack);
STACK * Create_node_stack(int cur);
#endif
