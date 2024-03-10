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
    FILE *file = fopen("in.txt", "r");
    int node_count, start, finish, edge_count;
    if(!fscanf(file, "%d", &node_count)){
        fclose(file);
        return 0;
    }
    if(fscanf(file, "%d %d", &start,&finish)!=2){
        fclose(file);
        return 0;
    }
    if(!fscanf(file, "%d", &edge_count)){
        fclose(file);
        return 0;
    }

    if (Check_for_errors(node_count, edge_count, start, finish) == 0)
        return 0;

    GRAPH * graph = Creating_graph(start, finish, node_count, edge_count);

    for (int i = 0; i < edge_count; i++){
        int st_edge, fn_edge, weight_edge;

        if(fscanf(file, "%d %d %d", &st_edge,&fn_edge, &weight_edge)!=3){
            fclose(file);
            return 0;
        }

        if (weight_edge < 0 || weight_edge > INT_MAX) {
            puts("bad length");
            return 0;
        }
        if (st_edge < 0 || st_edge > node_count || fn_edge < 0 || fn_edge > node_count){
            puts("bad vertex");
            return 0;
        }

        add_graph(st_edge, fn_edge, weight_edge, graph, node_count);
    }

    Deikstra_alg(graph);


    fclose(file);
    return 0;
}