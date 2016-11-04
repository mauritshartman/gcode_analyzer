#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

List *list_init(void)
{
    List *l = malloc(sizeof(List));
    memset(l, '\0', sizeof(List));

    l->data = malloc(sizeof(void *) * LIST_INITIAL_SIZE);
    memset(l->data, '\0', sizeof(void *) * LIST_INITIAL_SIZE);
    l->allocated = LIST_INITIAL_SIZE;

    l->length = 0;

    return l;
}


/* Append data to the end of the list, and return the number of items */
uint32 list_append(List *l, void *data)
{
    if (l->length >= l->allocated) {     /* Additional space is needed */
        if (realloc(l->data, l->allocated * 2) == NULL) {
            fprintf(stderr,"realloc() failed in file %s at line # %d", __FILE__,__LINE__);
            exit(EXIT_FAILURE);
        };
        l->allocated *= 2;
    }

    /* Assign the item */
    l->data[l->length++] = data;
    return l->length;
}


// Remove the item from the list (free its memory) and shift the remaining items to the left. */
void list_remove(List *l, uint32 index)
{   
    uint32 i;

    if (index >= l->length) {
        fprintf(stderr,"index out of range in file %s at line # %d", __FILE__,__LINE__);
        return;
    }

    free(l->data[index]);        // Deallocate the item at the specified index

    // Shift the remaining items to the left:
    for (i = index; i < (l->length - 1); i++) {
        l->data[i] = l->data[i + 1];
    }
    l->data[l->length - 1] = 0;
    l->length--;
}


// Return the item at the given index:
void *list_get(List *l, uint32 index)
{
    if (index >= l->length) {
        fprintf(stderr,"index out of range in file %s at line # %d", __FILE__,__LINE__);
        return NULL;
    }
    return l->data[index];
}


// Assign the new pointer at the specified index. Free the old pointer */
void list_set(List *l, uint32 index, void *data)
{
    if (index >= l->length) {
        fprintf(stderr,"index out of range in file %s at line # %d", __FILE__,__LINE__);
        return;
    }
    free(l->data[index]);
    l->data[index] = data;
}


/* Free the list and all the objects in it: */
void list_remove_all(List *l)
{
    uint32 i;

    for (i = 0; i< l->length; i++) {
        free(l->data[i]);
    }
    free(l->data);
    free(l);
}