#include <stdio.h>
#include <malloc.h>
#include "Graph_func.h"


int Check_for_errors(int node_count, int edge_count,
                     int start, int finish){              //checking for errors
    if (node_count > 5000 || node_count < 0) {
        puts("bad number of vertices");
        return 0;
    }

    if (edge_count < 0 || edge_count > node_count * (node_count + 1)/2){
        puts("bad number of edges");
        return 0;
    }

    if (start < 1 || start > node_count || finish < 1 || finish > node_count){
        puts("bad vertex");
        return 0;
    }

    return 1;
}


int main(){
    FILE *file = fopen("input.txt", "r");
    int node_count, start, finish, edge_count;

    if(!fscanf(file,  "%d", &node_count)){
        fclose(file);
        return 0;
    }


    if(fscanf(file,  "%d %d", &start, &finish) != 2){
        fclose(file);
        return 0;
    }

    if(!fscanf(file,  "%d", &edge_count)){
        fclose(file);
        return 0;
    }


    if (Check_for_errors(node_count, edge_count, start, finish) == 0)
        return 0;

    GRAPH *graph = Create_graph(node_count,
                                start, finish); //creating graph
                                                  //with adjacency_list
    int count = 0;
    for (int i = 0; i < edge_count; i++){
        int st_edge, fn_edge;
        long long int weight_edge;

        if(fscanf(file,  "%d %d %lld", &st_edge,&fn_edge, &weight_edge) != 3){
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

        Add_graph(graph, st_edge, fn_edge, weight_edge); //adding edge
        ++count;                                                //into graph

    }

    if (count < edge_count){
        puts("bad number of lines");
        return 0;
    }

    Djeikstra(graph);
    fclose(file);
    return 0;
}