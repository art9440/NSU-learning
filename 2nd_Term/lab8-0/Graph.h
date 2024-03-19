#ifndef NSU_LEARNING_GRAPH_H

#define NSU_LEARNING_GRAPH_H

#define GRAPH struct graph
#define SET struct set


GRAPH{
   int * edges;
   int node_count;
   int edge_count;
};

SET{
    int * parents;
    int * rank;
    int * visited;
};


GRAPH * Create_graph(GRAPH * graph, int node_count, int edge_count){
    graph = malloc( sizeof(GRAPH));
    if (graph == NULL)
        return NULL;
    graph -> node_count = node_count;
    graph -> edge_count = edge_count;
    graph -> edges =  malloc(3 * edge_count * sizeof(int));
    if (graph -> edges == NULL) {
        free(graph);
        return NULL;
    }

    return graph;
}


void add_edge(GRAPH * graph, int st_edge, int fn_edge,
              int weight_edge, int i){
    graph -> edges[3 * i] = st_edge;
    graph -> edges[3 * i + 1] = fn_edge;
    graph -> edges[3 * i + 2] = weight_edge;
}


SET * Create_set(SET * set, int node_count){
    set = malloc( sizeof(SET));
    set -> parents =  malloc(node_count * sizeof(int));
    set -> rank =  malloc(node_count * sizeof(int));
    set -> visited =  malloc(node_count * sizeof(int));

    for (int i = 0; i < node_count; i++){
        set -> rank[i] = 0;
        set -> visited[i] = 0;
        set -> parents[i] = i;
    }
    return set;

}


static int compare(const void *a, const void *b){
    const int *edge_a = a;
    const int *edge_b = b;
    return edge_a[2] - edge_b[2];
}


int find_parent(int * parents, int i){
    if (parents[i] == i)
        return i;
    return parents[i] = find_parent(parents, parents[i]);
}


void free_set(SET * set){
    free(set -> parents);
    free(set -> visited);
    free(set -> rank);
    free(set);
}


void print_res(GRAPH * graph){
    for (int i = 0; i < graph -> edge_count; i++)
        if (graph -> edges[i * 3 + 2] != -1)
            printf("%d %d\n", graph -> edges[3 * i], graph -> edges[3 * i + 1]);
}


void Kruskal(GRAPH * graph){
    int node_count = graph -> node_count;
    int edge_count = graph -> edge_count;
    SET * set = NULL;
    set = Create_set(set, node_count);
    for (int i = 0; i < edge_count; i++){
        int start = graph -> edges[i * 3];
        int finish = graph -> edges[i * 3 + 1];
        int fromSet = find_parent(set -> parents, start - 1);
        int toSet = find_parent(set -> parents, finish - 1);
        if (fromSet != toSet){
            set -> visited[start - 1] = 1;
            set -> visited[finish - 1] = 1;
            if (set -> rank[fromSet] < set -> rank[toSet]){
                int tmp = fromSet;
                fromSet = toSet;
                toSet = tmp;
            }
            set -> parents[toSet] = fromSet;
            if (set -> rank[fromSet] == set -> rank[toSet])
                (set -> rank[fromSet])++;
        }
        else
            graph -> edges[3 * i + 2] = -1;
    }
    for(int i = 0; i < node_count; i++){
        if (!set -> visited[i]){
            puts("no spanning tree");
            free_set(set);
            return;
        }
    }
    print_res(graph);
    free_set(set);
}


#endif
