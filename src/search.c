#include "../inc/search_algorithms.h"

int *search_algorithms_internal_create_array(int x1, int x2)
{
    int *array = malloc(sizeof(int) * 2);
    array[0] = x1;
    array[1] = x2;
    return array;
}

SA_BfsSearchResults *search_algorithms_bfs(CS_SList *graph_adjacency_list, int start, int goal)
{
    CS_SList *search_tree = c_structures_s_list_create();
    CS_SList *border = c_structures_s_list_create();

    // Add start item to border
    c_structures_s_list_append(border, search_algorithms_internal_create_array(start, start));

    int *active_border_item;

    while (border->length > 0)
    {
        // Update current node to whichever element of the active border item is different from it
        active_border_item = (int *)c_structures_s_list_get_item(border, 0)->data;
        c_structures_s_list_remove(border, 0);
        c_structures_s_list_append(search_tree, active_border_item);

        if (active_border_item[1] == goal)
        {
            SA_BfsSearchResults *search_results = malloc(sizeof *search_results);
            search_results->border = border;
            // Remove start item from search tree
            c_structures_s_list_remove(search_tree, 0);
            search_results->search_tree = search_tree;
            search_results->found = 1;
            return search_results;
        }
        // Find neighbors of current node and add them to the border
        CS_SListItem *item = graph_adjacency_list->head;
        for (size_t i = 0; i < graph_adjacency_list->length; i++)
        {
            int *connection = item->data;
            if (connection[0] == active_border_item[1] && connection[1] != active_border_item[0])
            {
                c_structures_s_list_append(border, connection);
            }
            else if (connection[1] == active_border_item[1] && connection[0] != active_border_item[0])
            {
                c_structures_s_list_append(border, search_algorithms_internal_create_array(connection[1], connection[0]));
            }
            item = item->next;
        }
    }

    SA_BfsSearchResults *bfs_search_results = malloc(sizeof *bfs_search_results);
    bfs_search_results->border = border;
    bfs_search_results->search_tree = search_tree;
    bfs_search_results->found = 0;
    return bfs_search_results;
}

int search_algorithms_internal_compare_int_callback(void *data1, void *data2)
{
    int *a = data1;
    int *b = data2;
    if (*a == *b)
    {
        return 1;
    }
    return 0;
}

SA_DfsSearchResults *
search_algorithms_dfs(CS_SList *graph_adjacency_list, int start, int goal)
{
    // Create node stack and search tree
    CS_Stack *node_stack = c_structures_stack_create();
    CS_Stack *visited_nodes = c_structures_s_list_create();
    CS_Tree *search_tree = c_structures_tree_create();
    // Create current node with start id
    CS_TreeNode *current_node = c_structures_tree_node_create(start, NULL);
    // Add node to root of search tree
    c_structures_tree_add_root_node(search_tree, current_node);

    // Add node to stack
    c_structures_stack_push(node_stack, current_node);

    while (node_stack->length > 0)
    {
        // Get next node from stack
        current_node = c_structures_stack_pop(node_stack)->data;
        // Add current node id to visited nodes list
        c_structures_s_list_append(visited_nodes, &current_node->id);

        // Check if node is the goal
        if (current_node->id == goal)
        {
            SA_DfsSearchResults *dfs_result = malloc(sizeof *dfs_result);
            dfs_result->found = 1;
            dfs_result->search_tree = search_tree;
            return dfs_result;
        }

        // Find neighbors of current node
        CS_SListItem *graph_item = graph_adjacency_list->head;
        int index = 0;
        while (graph_item != NULL)
        {
            int *connection = graph_item->data;
            SA_TreeNodeData *current_node_data = current_node->data;

            // Check if current node's parents id is equal to connection[1] or connection[0]
            int parent_eq_connection_0 = 0;
            int parent_eq_connection_1 = 0;
            if (current_node_data != NULL)
            {
                if (current_node_data->parent_id == connection[0])
                {
                    parent_eq_connection_0 = 1;
                }
                if (current_node_data->parent_id == connection[1])
                {
                    parent_eq_connection_1 = 1;
                }
            }

            // TODO: check if connections have been visited
            int already_visited_connection_0 = 0;
            int already_visited_connection_1 = 0;
            if (c_structures_s_list_index_of(visited_nodes,
                                             &connection[0],
                                             search_algorithms_internal_compare_int_callback) != -1)
            {
                already_visited_connection_0 = 1;
            }
            if (c_structures_s_list_index_of(visited_nodes,
                                             &connection[1],
                                             search_algorithms_internal_compare_int_callback) != -1)
            {
                already_visited_connection_1 = 1;
            }

            if (connection[0] == current_node->id && !parent_eq_connection_1 && !already_visited_connection_1)
            {
                // Create data for new node
                SA_TreeNodeData *new_node_data = malloc(sizeof *new_node_data);
                new_node_data->parent_id = current_node->id;
                // Create new node with id of neighbor
                CS_TreeNode *new_node = c_structures_tree_node_create(connection[1], new_node_data);
                // Add node to stack
                c_structures_stack_push(node_stack, new_node);
                // Add node as child on tree
                c_structures_tree_node_add_child(current_node, new_node);
            }
            else if (connection[1] == current_node->id && !parent_eq_connection_0 && !already_visited_connection_0)
            {
                // Create data for new node
                SA_TreeNodeData *new_node_data = malloc(sizeof *new_node_data);
                new_node_data->parent_id = current_node->id;
                // Create new node with id of neighbor
                CS_TreeNode *new_node = c_structures_tree_node_create(connection[0], new_node_data);
                // Add node to stack
                c_structures_stack_push(node_stack, new_node);
                // Add node as child on tree
                c_structures_tree_node_add_child(current_node, new_node);
            }

            // Update graph item
            graph_item = graph_item->next;
            index++;
        }
    }
    // Set return value in case goal was not found
    SA_DfsSearchResults *dfs_result = malloc(sizeof *dfs_result);
    dfs_result->found = 0;
    dfs_result->search_tree = search_tree;
    return dfs_result;
}