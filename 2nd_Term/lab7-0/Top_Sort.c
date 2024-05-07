#include <stdio.h>
#include "Top_sort_func.h"


int Check_for_errors(int node_count, int edge_count){
    if (node_count > 2000 || node_count < 0) {
        puts("bad number of vertices");
        return 0;
    }

    if (edge_count < 0 || edge_count > node_count * (node_count + 1)/2){
        puts("bad number of edges");
        return 0;
    }

    return 1;
}


int main(){
    FILE *file = fopen("input.txt", "r");
    int node_count, edge_count;
    GRAPH * graph = NULL;

    if(fscanf(file,  "%d %d", &node_count, &edge_count) != 2){
        puts("bad number of lines");
        fclose(file);
        return 0;
    }



    if (Check_for_errors(node_count, edge_count) == 0)
        return 0;

    graph = Create_graph(graph, node_count);

    int count_err = 0;
    for (int i = 0 ; i < edge_count; i++){
        int st_edge, fn_edge;

        if (fscanf(file, "%d %d", &st_edge, &fn_edge) != 2) {
            puts("bad number of lines");
            fclose(file);
            return 0;
        }

        if (st_edge < 0 || st_edge > node_count || fn_edge < 0
            || fn_edge > node_count){
            puts("bad vertex");
            return 0;
        }

        add_edge(graph, st_edge, fn_edge);
        count_err++;
    }


    if (count_err < edge_count){
        puts("bad number of lines");
        return 0;
    }

    Top_Sort(graph);

    fclose(file);

    return 0;
}