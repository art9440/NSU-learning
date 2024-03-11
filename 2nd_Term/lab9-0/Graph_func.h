#ifndef NSU_LEARNING_GRAPH_FUNC_H
#define NSU_LEARNING_GRAPH_FUNC_H

#define NODE struct node
#define GRAPH struct graph
#define SHORTEST_PATH struct shortest_path


NODE{
    int vertex;
    long long weight;
    NODE * next;
};


GRAPH{
    int vertex;
    int start;
    int finish;
    NODE ** adj_list;
};


SHORTEST_PATH{
    long long int * ways;
    int * processed;
    int * progenitors;
};


void Create_graph(GRAPH * graph, int start, int finish, int node_count){
    graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph -> vertex = node_count;
    graph -> start = start;
    graph -> finish = finish;
    graph -> adj_list = (NODE**) malloc(node_count * sizeof(NODE*));
    for (int i = 0;i < node_count; i++)
        graph -> adj_list[i] = NULL;
}


void Add_graph(GRAPH * graph, int st_edge, int fn_edge, int weight_edge){
    NODE * node = (NODE*)malloc(sizeof(NODE));
    node -> vertex = fn_edge;
    node -> weight = weight_edge;
    node -> next = graph -> adj_list[st_edge - 1];
    graph -> adj_list[st_edge - 1] = node;
}


void Djeikstra(GRAPH * graph){
    int vertex = graph -> vertex;
    int start = graph -> start;
    int finish = graph -> finish;


    SHORTEST_PATH* path = (SHORTEST_PATH*)malloc(vertex *sizeof(SHORTEST_PATH));

    for (int i = 0; i < vertex; i++) {
        path->ways[i] = LLONG_MAX;
        path->processed[i] = 0;
        path->progenitors[i] = -1;
    }

    path->ways[start - 1] = 0;

}





#endif
