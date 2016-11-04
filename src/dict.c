#include <dict.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Dict *dict_init(void)
{
    Dict *d = malloc(sizeof(Dict));
    d->keys = malloc(sizeof(ubyte *) * DICT_INITIAL_SIZE);
    d->data = malloc(sizeof(void *) * DICT_INITIAL_SIZE);

    memset(d, '\0', sizeof(Dict));
    memset(d->keys, '\0', sizeof(ubyte *) * DICT_INITIAL_SIZE);
    memset(d->data, '\0', sizeof(void *) * DICT_INITIAL_SIZE);
    
    d->allocated = DICT_INITIAL_SIZE;
    d->length = 0;

    return d;
}


/* True iff the key exists in the dictionary: */
bool dict_key_exists(Dict *d, ubyte *key)
{
    uint32 i;

    // Loop through the dict keys:
    for (i = 0; i < d->length; i++) {
        if (!strcmp((char *)key, (char *)(d->keys[i]))) { return true; }
    }

    return false;
}


/* Add the data to the given key. If the key already exists, update the data. */
void dict_set(Dict *d, ubyte *key,void *data)
{
    uint32 i;

    // Loop through the dict keys:
    for (i = 0; i < d->length; i++) {
        if (!strcmp((char *)key, (char *)(d->keys[i]))) {
            d->data[i] = data;
            return;
        }
    }

    // If not, check for space and add the key:
    if (d->length >= d->allocated) {     /* Additional space is needed */
        if (realloc(d->keys, d->allocated * 2) == NULL) {
            fprintf(stderr,"realloc() failed in file %s at line # %d", __FILE__,__LINE__);
            exit(EXIT_FAILURE);
        };
        if (realloc(d->data, d->allocated * 2) == NULL) {
            fprintf(stderr,"realloc() failed in file %s at line # %d", __FILE__,__LINE__);
            exit(EXIT_FAILURE);
        };
        d->allocated *= 2;
    }

    /* Assign the item */
    d->data[d->length] = data;
    d->keys[d->length] = key;
    d->length++;
}


// Search for the given key and remove the data (free memory as well):
void dict_remove(Dict *d, ubyte *key)
{
    uint32 i, j;

    // Loop through the dict keys:
    for (i = 0; i < d->length; i++) {
        if (!strcmp((char *)key, (char *)(d->keys[i]))) {
            // Key found: remove the data and shift all subsequent keys left:
            free(d->data[i]);
            for (j = i; j < (d->length - 1); j++) {
                d->keys[j] = d->keys[j + 1];
                d->data[j] = d->data[j + 1];
            }
            d->keys[d->length - 1] = 0;
            d->data[d->length - 1] = 0;
            d->length--;
            return;
        }
    }
    // TODO If not found, do nothing?
}


void *dict_get(Dict *d, ubyte *key)
{
    uint32 i;

    // Loop through the dict keys:
    for (i = 0; i < d->length; i++) {
        if (!strcmp((char *)key, (char *)(d->keys[i]))) {
            return d->data[i];
        }
    }

    return NULL;
}


void dict_remove_all(Dict *d)
{
    uint32 i;

    for (i = 0; i < d->length; i++) {
        free(d->data[i]);
    }

    free(d->keys);      // TODO memory leak; remove string pointers too?
    free(d->data);
    free(d);
}