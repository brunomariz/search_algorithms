#ifndef _QUEEN_PROBLEM_H
#define _QUEEN_PROBLEM_H

#include <SDL2/SDL.h>
#include "../c_trees/inc/c_trees.h"
#include "../c_trees/c_structures/inc/c_structures.h"

// ===Conversion===
int *queen_problem_s_list_to_int_1_2_array(CS_SList *list);
// ===Rendering===
void queen_problem_render_polar_axis(SDL_Renderer *renderer);
void queen_problem_render_tree_adj_list(SDL_Renderer *renderer, CT_AdjListTree tree);
void queen_problem_render_tree_nested_obj(SDL_Renderer *renderer, CS_TreeNode *root_node);
// ===Search===
typedef struct
{
    CS_SList *search_tree;
    CS_SList *border;
    int found;
} QP_BfsSearchResults;

typedef struct
{
    CS_Tree *search_tree;
    int found;
} QP_DfsSearchResults;

typedef struct
{
    int parent_id;
} QP_TreeNodeData;

QP_BfsSearchResults *queen_problem_bfs(CS_SList *graph_adjacency_list, int start, int goal);
QP_DfsSearchResults *queen_problem_dfs(CS_SList *graph_adjacency_list, int start, int goal);

#endif
