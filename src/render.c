#include "../inc/search_algorithms.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

CT_RGBA white = {255, 255, 255, 255};
CT_RGBA red = {255, 0, 0, 255};

void search_algorithms_render_polar_axis(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    int thick_border = 0;

    int center_x = CT_WINDOW_WIDTH / 2;
    int center_y = CT_WINDOW_HEIGHT / 2;
    for (int i = 40; i < 440; i += 40)
    {
        c_trees_draw_circumference(renderer, CT_WINDOW_WIDTH / 2, CT_WINDOW_HEIGHT / 2, i, (CT_RGBA){100, 100, 100, 255}, thick_border);
    }

    for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / 20)
    {
        int dest_x = (int)(cos(theta) * CT_WINDOW_WIDTH + CT_WINDOW_WIDTH / 2);
        int dest_y = (int)(sin(theta) * CT_WINDOW_HEIGHT + CT_WINDOW_HEIGHT / 2);

        SDL_RenderDrawLine(renderer, center_x, center_y, dest_x, dest_y);
    }
    SDL_RenderDrawLine(renderer, CT_WINDOW_WIDTH / 2, 0, CT_WINDOW_WIDTH / 2, CT_WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, CT_WINDOW_HEIGHT / 2, CT_WINDOW_WIDTH, CT_WINDOW_HEIGHT / 2);
}

void search_algorithms_render_tree_adj_list(SDL_Renderer *renderer, CT_AdjListTree tree)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    search_algorithms_render_polar_axis(renderer);
    c_trees_draw_tree_level_based_polar_adj_list(renderer, tree, 1, 0, 0, 2 * 3.1415926);
}

void search_algorithms_render_tree_nested_obj(SDL_Renderer *renderer, CS_TreeNode *root_node)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    search_algorithms_render_polar_axis(renderer);
    c_trees_draw_tree_level_based_polar_nested_obj(renderer, root_node, 0, 0, 2 * 3.1415962);
}
