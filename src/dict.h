/*
 * Generic dictionary utlity class
 */

#ifndef DICT_H
#define DICT_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <defs.h>

#define DICT_INITIAL_SIZE 32

/* Generic dict */
typedef struct {
    ubyte **keys;
    void **data;
    uint32 allocated;
    uint32 length;
} Dict;


Dict *dict_init(void);
void dict_remove(Dict *, ubyte *);
bool dict_key_exists(Dict *, ubyte *);
void *dict_get(Dict *, ubyte *);
void dict_set(Dict *, ubyte *, void *);
void dict_remove_all(Dict *);


#ifdef  __cplusplus
}
#endif
 
#endif  /*DICT_H */