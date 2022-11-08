#ifndef _SEARCH_ALGORITHMS_H
#define _SEARCH_ALGORITHMS_H

#include <SDL2/SDL.h>
#include "../c_trees/inc/c_trees.h"
#include "../c_trees/c_structures/inc/c_structures.h"

// ===Conversion===
int *search_algorithms_s_list_to_int_1_2_array(CS_SList *list);
// ===Rendering===
void search_algorithms_render_polar_axis(SDL_Renderer *renderer);
void search_algorithms_render_tree_adj_list(SDL_Renderer *renderer, CT_AdjListTree tree);
void search_algorithms_render_tree_nested_obj(SDL_Renderer *renderer, CS_TreeNode *root_node);
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
    int found;
} SA_DfsSearchResults;

typedef struct
{
    int parent_id;
} SA_TreeNodeData;

SA_BfsSearchResults *search_algorithms_bfs(CS_SList *graph_adjacency_list, int start, int goal);
SA_DfsSearchResults *search_algorithms_dfs(CS_SList *graph_adjacency_list, int start, int goal);

#endif
