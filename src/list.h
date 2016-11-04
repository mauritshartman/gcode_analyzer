/*
 * Generic list utlity class
 */

#ifndef LIST_H
#define LIST_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <defs.h>

#define LIST_INITIAL_SIZE 32

/* Generic linked list */
typedef struct {
    void **data;
    uint32 allocated;
    uint32 length;
} List;


List *list_init(void);
uint32 list_append(List *, void *);
void list_remove(List *, uint32);
void *list_get(List *, uint32);
void list_set(List *, uint32, void *);
void list_remove_all(List *);


#ifdef  __cplusplus
}
#endif
 
#endif  /* LIST_H */