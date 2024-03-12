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


int minDistance(NODE * priority, SHORTEST_PATH * path){
    if (!priority)
        return -1;

    long long min_way = LLONG_MAX;
    int min_vertex = -1;
    NODE * cur = priority;

    while (cur){
        int vertex = cur -> vertex;
        if (!(path -> processed[vertex]) && path -> ways[vertex] <= min_way){
            min_way = path -> ways[vertex];
            min_vertex = vertex;
        }
        cur = cur -> next;
    }

    return min_vertex;
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

    NODE * priority = NULL;

    NODE* nw_Node = (NODE*)malloc(sizeof(NODE));
    nw_Node->vertex = start - 1;
    nw_Node->weight = 0;
    nw_Node->next = NULL;
    priority = nw_Node;

    while (priority){
        int min_edge = minDistance(priority, path);
        if (min_edge == -1)
            break;

        path -> processed[min_edge] = 1;

        NODE * interim = graph -> adj_list[min_edge];
        while (interim){
            int adj_vert = interim -> vertex - 1;
            long long alter_vertex = path -> ways[min_edge] + interim -> weight;

            if (alter_vertex <= path ->ways[adj_vert]){
                path -> ways[adj_vert] = alter_vertex;
                path -> progenitors[adj_vert] = min_edge;

                NODE * nw_node = (NODE*)malloc(sizeof(NODE));
                nw_node -> vertex = adj_vert;
                nw_node -> weight = alter_vertex;
                nw_node -> next =priority;
                priority = nw_node;
            }
            interim = interim -> next;
        }
    }

    int way[graph -> vertex];
    int way_len = 0;

    int nw_cur = graph -> finish - 1;
    while (nw_cur != -1){
        way[way_len++] = nw_cur + 1;
        nw_cur = path -> progenitors[nw_cur];
    }

    for (int i = 0; i < graph -> vertex; i++){
        if (path -> ways[i] == LLONG_MAX)
            printf("oo ");
        else if(path -> ways[i] > INT_MAX)
            printf("INT_MAX+ ");
        else
            printf("%lld", path -> ways[i] - path -> ways[start - 1]);
    }
    puts("\n");

    int check_1 = 0;
    int check_2 = 0;

    for (int i = 0; i < way_len; i++){
        if (way[i] == start || way[i] == finish)
            check_1++;
        if (path -> ways[i + 1] == INT_MAX && path -> ways[i + 1] != LLONG_MAX)
            check_2++;
    }

    if (check_2 != 2 && start != finish){
        puts("no path");
        return;
    }
    else if(path -> ways[way_len - 1] > INT_MAX && check_2 > 2){
        puts("overflow");
        return;
    }

    for (int i = 0; i < way_len; i++)
        printf("%d", way[i]);

    puts("\n");
}

#endif
