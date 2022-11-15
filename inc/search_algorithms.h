#ifndef _SEARCH_ALGORITHMS_H
#define _SEARCH_ALGORITHMS_H

#include <SDL2/SDL.h>
#include "../c_plot/inc/c_plot.h"
#include "../c_plot/c_structures/inc/c_structures.h"

// ===Search===
typedef struct
{
    CS_SList *search_tree;
    CS_SList *border;
    int found;
} SA_BfsSearchResults;

typedef struct
{
    CS_Tree *search_tree;
    CS_SList *path;
    int found;
} SA_DfsSearchResults;

typedef struct
{
    CS_TreeNode *parent_node;
} SA_DfsTreeNodeData;

SA_BfsSearchResults *search_algorithms_bfs(CS_SList *graph_adjacency_list, int start, int goal);
SA_DfsSearchResults *search_algorithms_dfs(CS_SList *graph_adjacency_list, int start, int goal);

#endif
