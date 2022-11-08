#include "../inc/search_algorithms.h"

int *search_algorithms_s_list_to_int_1_2_array(CS_SList *list)
{
    int *array = malloc(sizeof(int) * list->length * 2);
    CS_SListItem *item = list->head;
    for (int i = 0; i < list->length; i++)
    {
        array[i * 2 + 0] = ((int *)item->data)[0];
        array[i * 2 + 1] = ((int *)item->data)[1];
        item = item->next;
    }
    return array;
}