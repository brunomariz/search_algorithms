#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "../inc/search_algorithms.h"
#include "../c_plot/inc/c_plot.h"
#include "../c_plot/c_structures/inc/c_structures.h"

int event_handler(SDL_Event event);

void df_example_internal_print_list_callback(void *data, int iter)
{
    int *array = (int *)data;
    printf("%d:\t[%d, %d]\n", iter, array[0], array[1]);
}

int main(void)
{

    // Create graph for BFS Search
    CS_SList *adjacency_list = c_structures_s_list_create();
    int c1[2] = {1, 3};
    int c2[2] = {1, 2};
    int c3[2] = {2, 4};
    int c4[2] = {4, 5};
    int c5[2] = {4, 6};
    int c6[2] = {5, 8};
    int c7[2] = {5, 7};
    int c8[2] = {6, 8};
    int c9[2] = {6, 7};
    int c10[2] = {8, 9};
    int c11[2] = {7, 9};
    // int c12[2] = {6, 10};
    int c13[2] = {3, 10};
    int c14[2] = {10, 11};
    int c15[2] = {10, 12};
    c_structures_s_list_append(adjacency_list, c1);
    c_structures_s_list_append(adjacency_list, c2);
    c_structures_s_list_append(adjacency_list, c3);
    c_structures_s_list_append(adjacency_list, c4);
    c_structures_s_list_append(adjacency_list, c5);
    c_structures_s_list_append(adjacency_list, c6);
    c_structures_s_list_append(adjacency_list, c7);
    c_structures_s_list_append(adjacency_list, c8);
    c_structures_s_list_append(adjacency_list, c9);
    c_structures_s_list_append(adjacency_list, c10);
    c_structures_s_list_append(adjacency_list, c11);
    // c_structures_s_list_append(adjacency_list, c12);
    c_structures_s_list_append(adjacency_list, c13);
    c_structures_s_list_append(adjacency_list, c14);
    c_structures_s_list_append(adjacency_list, c15);

    // Run dfs search algorith
    SA_DfsSearchResults *dfs_search_results = search_algorithms_dfs(adjacency_list, 1, 12);

    // Print path found
    printf("Path:\n");
    c_structures_s_list_print(dfs_search_results->path, df_example_internal_print_list_callback);

    c_plot_tree_show(dfs_search_results->search_tree->root_nodes->head->data);
}