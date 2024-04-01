#ifndef NSU_LEARNING_TOP_SORT_FUNC_H
#define NSU_LEARNING_TOP_SORT_FUNC_H

#define GRAPH struct graph
#define QUEUE struct queue

GRAPH{
    int node_count;
    char * adj_matrix;
};

QUEUE{
    int * qu;
    int rear, front;
};



GRAPH * Create_graph(GRAPH * graph, int node_count);
void add_edge(GRAPH * graph, int st_edge, int fn_edge);
void Top_Sort(GRAPH * graph);
void Create_queue(QUEUE ** queue, int node_count);
void Enqueue(QUEUE * queue, int cur);
int isEmpty(QUEUE * queue);
int Dequeue(QUEUE * queue);
void free_all(GRAPH * graph, QUEUE * q);
#endif
