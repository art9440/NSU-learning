#ifndef NSU_LEARNING_KOSARAJU_FUNC_H
#define NSU_LEARNING_KOSARAJU_FUNC_H

#define GRAPH struct graph
#define STACK struct stack

GRAPH{
    int node_count;
    char * adj_matrix;
    char * rev_adj_matrix;
};

STACK{
    int * data;
    int top;
};


GRAPH * Create_graph(GRAPH * graph, int node_count);
void add_edge(GRAPH * graph, int st_edge, int fn_edge);
void Kosaraju(GRAPH * graph);
void Create_stack(STACK * stack, int node_count);
void push_stack(STACK * stack, int cur);
void dfs(GRAPH* graph, int cur, int* visited, STACK * stack);
int pop_stack(STACK * stack);
void find_SCC(GRAPH * graph, STACK * stack, int * visited);
void dfs_for_result(GRAPH * graph, int * visited, int cur, int colour);
void free_all(GRAPH * graph, STACK * stack, int * arr);
void print_res(int * visited, int node_count);
#endif
