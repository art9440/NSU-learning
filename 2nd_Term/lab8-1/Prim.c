#include <stdio.h>
#include <stdlib.h>
#include "Prim_function.h"

int Check_for_errors(int node_count, int edge_count){
    if (node_count > 5000 || node_count < 0) {
        puts("bad number of vertices");
        return 0;
    }

    if (edge_count < 0 || edge_count > node_count * (node_count + 1)/2){
        puts("bad number of edges");
        return 0;
    }
    if (edge_count == 0 && node_count == 0) {
        puts("no spanning tree");
        return 0;
    }
    if(edge_count == 0 && node_count == 1){
        return 0;
    }

    return 1;
}


int main(){
    FILE *file = fopen("input.txt", "r");
    int node_count, edge_count;
    GRAPH * graph = NULL;


    if(!fscanf(file,  "%d", &node_count)){
        fclose(file);
        return 0;
    }

    if(!fscanf(file,  "%d", &edge_count)){
        fclose(file);
        return 0;
    }

    if (Check_for_errors(node_count, edge_count) == 0)
        return 0;

    graph = Create_graph(graph, node_count);

    int count = 0;
    for (int i = 0; i < edge_count; i++) {
        int st_edge, fn_edge;
        long long int weight_edge;

        if (fscanf(file, "%d %d %lld", &st_edge,
                   &fn_edge, &weight_edge)!= 3){
            puts("bad number of lines");
            fclose(file);
            return 0;
        }

        if (weight_edge < 0 || weight_edge > INT_MAX) {
            puts("bad length");
            return 0;
        }

        if (st_edge < 0 || st_edge > node_count || fn_edge < 0
                || fn_edge > node_count){
            puts("bad vertex");
            return 0;
        }
        add_edge(st_edge - 1, fn_edge - 1, weight_edge, graph);

        ++count;
    }

    Prim_alg(graph);

    if (count < edge_count){
        puts("bad number of lines");
        return 0;
    }

    fclose(file);
    return 0;
}


