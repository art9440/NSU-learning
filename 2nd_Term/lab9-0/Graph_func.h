#ifndef NSU_LEARNING_GRAPH_FUNC_H
#define NSU_LEARNING_GRAPH_FUNC_H

#define NODE struct node
#define GRAPH struct graph
#define SHORTEST_PATH struct shortest_path


NODE
{
    int vertex;
    long long int weight;
    NODE* next;
};


GRAPH
{
    int vertex;
    NODE** adj_list;
};


SHORTEST_PATH
{
    long long int  ways;
    int  processed;
    int  progenitors;
};


GRAPH* Create_graph(int vert)
{
    GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph -> vertex = vert;
    graph -> adj_list = (NODE**)malloc(vert * sizeof(NODE*));
    for (int i = 0; i < vert; i++)
        graph -> adj_list[i] = NULL;

    return graph;
}


NODE* Create_node(int vertex, long long weight)
{
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node -> vertex = vertex;
    node -> weight = weight;
    node -> next = NULL;
    return node;
}


void Add_graph(GRAPH* graph, int st_edge, int fn_edge, long long int weight)
{
    NODE* node = Create_node(fn_edge, weight);
    node -> next = graph -> adj_list[st_edge - 1];
    graph -> adj_list[st_edge - 1] = node;

    node = Create_node(st_edge, weight);
    node -> next = graph -> adj_list[fn_edge - 1];
    graph -> adj_list[fn_edge - 1] = node;
}


int minDistance(NODE* priority, SHORTEST_PATH* path) //counting min distance to vertex
{
    if (!priority)
        return -1;

    long long int min_way = LLONG_MAX;
    int min_vertex = -1;
    NODE* cur = priority;

    while (cur != NULL)
    {
        int vertex = cur -> vertex;
        if (!(path[vertex].processed) && path[vertex].ways
                                         <= min_way)
        {
            min_way = path[vertex].ways;
            min_vertex = vertex;
        }
        cur = cur -> next;
    }
    return min_vertex;
}


void Djeikstra(GRAPH* graph, int start, int finish){
    SHORTEST_PATH* path = (SHORTEST_PATH*)malloc(graph
            -> vertex *sizeof(SHORTEST_PATH));

    for (int i = 0; i < graph -> vertex; i++)
    {
        path[i].ways = LLONG_MAX;
        path[i].processed = 0;
        path[i].progenitors = -1;
    }

    path[start - 1].ways = 0;
    NODE* priority = NULL;

    NODE* nw_Node = (NODE*)malloc(sizeof(NODE));
    nw_Node -> vertex = start - 1;
    nw_Node -> weight = 0;
    nw_Node -> next = NULL;
    priority = nw_Node;

    while (priority != NULL)
    {
        int min_edge = minDistance(priority, path);
        if (min_edge == -1)
            break;


        path[min_edge].processed = 1;

        NODE* interim = graph -> adj_list[min_edge];

        while (interim != NULL)
        {
            int adj_vertex = interim -> vertex - 1;
            long long int alter_vertex = path[min_edge].ways +
                    interim -> weight;

            if (alter_vertex <= path[adj_vertex].ways)
            {
                path[adj_vertex].ways = alter_vertex;
                path[adj_vertex].progenitors = min_edge;

                NODE* node = (NODE*)malloc(sizeof(NODE));
                node -> vertex = adj_vertex;
                node -> weight = alter_vertex;
                node -> next = priority;
                priority = node;
            }
            interim = interim -> next;
        }
    }

    int way[graph -> vertex];
    int way_len = 0;

    int cur = finish - 1;
    while (cur != -1)
    {
        way[way_len++] = cur + 1;
        cur = path[cur].progenitors;
    }

    for (int i = 0; i < graph->vertex; i++)
    {
        if (path[i].ways == LLONG_MAX)
            printf("oo ");
        else if (path[i].ways > INT_MAX)
            printf("INT_MAX+ ");
        else
            printf("%lld ", path[i].ways -
                            path[start - 1].ways);
    }
    printf("\n");

    int check1 = 0;
    int check2 = 0;

    for (int i = 0; i < way_len; i++)
    {
        if (way[i] == start || way[i] == finish)
            ++check1;
        if (path[i + 1].ways >= INT_MAX &&
            path[i + 1].ways != LLONG_MAX)
            ++check2;
    }

    if (check1 != 2 && start != finish)
    {
        puts("no path");
        return;
    }
    else if (path[way_len - 1].ways > INT_MAX && check2 > 2)
    {
        puts("overflow");
        return;
    }

    for (int i = 0; i < way_len; i++)
        printf("%d ", way[i]);

    puts("\n");
    free(graph);
}

#endif
