#include "../c_trees/inc/c_trees.h"
#include "../inc/search_algorithms.h"
#include "../c_trees/c_structures/inc/c_structures.h"

void test_internal_print_list_callback(void *data, int iter)
{
    int *array = (int *)data;
    printf("%d:\t[%d, %d]\n", iter, array[0], array[1]);
}

int main()
{
    CS_SList *adjacency_list = c_structures_s_list_create();
    int c1[2] = {1, 2};
    int c2[2] = {1, 3};
    int c3[2] = {2, 4};
    int c4[2] = {2, 5};
    int c5[2] = {3, 4};
    int c6[2] = {3, 5};
    int c7[2] = {5, 6};
    int c8[2] = {4, 6};
    c_structures_s_list_append(adjacency_list, c1);
    c_structures_s_list_append(adjacency_list, c2);
    c_structures_s_list_append(adjacency_list, c3);
    c_structures_s_list_append(adjacency_list, c4);
    c_structures_s_list_append(adjacency_list, c5);
    c_structures_s_list_append(adjacency_list, c6);
    c_structures_s_list_append(adjacency_list, c7);
    c_structures_s_list_append(adjacency_list, c8);
    printf("Adjacency list (graph):\n");
    c_structures_s_list_print(adjacency_list, test_internal_print_list_callback);

    SA_DfsSearchResults *dfs_search_results = search_algorithms_dfs(adjacency_list, 1, 4);
    printf("Search tree:\n");
    c_structures_tree_print(dfs_search_results->search_tree);
    printf("Found: %d\n", dfs_search_results->found);

    return 0;
}