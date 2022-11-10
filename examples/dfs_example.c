#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "../c_trees/inc/c_trees.h"
#include "../inc/search_algorithms.h"
#include "../c_trees/c_structures/inc/c_structures.h"

int event_handler(SDL_Event event);

void df_example_internal_print_list_callback(void *data, int iter)
{
    int *array = (int *)data;
    printf("%d:\t[%d, %d]\n", iter, array[0], array[1]);
}

int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("C_TREES",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       CT_WINDOW_WIDTH, CT_WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

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

    // animation loop
    int close_requested = 0;
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            close_requested = event_handler(event);
        }

        // Call render function
        search_algorithms_render_tree_nested_obj(rend, dfs_search_results->search_tree->root_nodes->head->data);

        SDL_RenderPresent(rend);
    }

    // clean up resources before exiting
    if (rend)
    {
        SDL_DestroyRenderer(rend);
    }
    if (win)
    {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
}

int event_handler(SDL_Event event)
{
    int close_requested = 0;
    if (event.type == SDL_QUIT)
    {
        close_requested = 1;
    }
    return close_requested;
}