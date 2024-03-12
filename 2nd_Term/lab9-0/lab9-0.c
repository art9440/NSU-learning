#include <stdio.h>
#include <malloc.h>
#include "Graph_func.h"


int Check_for_errors(int node_count, int edge_count, int start, int finish){
    if (node_count > 5000 || node_count < 0) {
        puts("bad number of vertices");
        return 0;
    }

    if (edge_count < 0 || edge_count > node_count * (node_count + 1)/2) {
        puts("bad number of edge");
        return 0;
    }

    if (start < 0 || start > node_count || finish < 0 || finish > node_count){
        puts("bad vertex");
        return 0;
    }

    return 1;
}


int main(){
    int node_count, start, finish, edge_count;
    GRAPH *graph;
    scanf( "%d", &node_count);

    scanf( "%d %d", &start,&finish);

    scanf( "%d", &edge_count);


    if (Check_for_errors(node_count, edge_count, start, finish) == 0)
        return 0;

    Create_graph(graph, start, finish, node_count);     //creating graph with adjacency_list

    int count = 0;
    for (int i = 0; i < edge_count; i++){
        int st_edge, fn_edge, weight_edge;

        scanf( "%d %d %d", &st_edge,&fn_edge, &weight_edge);

        if (weight_edge < 0 || weight_edge > INT_MAX) {
            puts("bad length");
            return 0;
        }
        if (st_edge < 0 || st_edge > node_count || fn_edge < 0 || fn_edge > node_count){
            puts("bad vertex");
            return 0;
        }

        Add_graph(graph, st_edge, fn_edge, weight_edge);
        count++;

    }

    if (count < edge_count){
        puts("bad number of lines");
        return 0;
    }

   Djeikstra(graph);

    return 0;
}