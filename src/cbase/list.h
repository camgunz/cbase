#pragma once

#ifndef LIST_H__
#define LIST_H__

enum {
    LIST_EMPTY = 1,
    DLIST_EMPTY,
    DLIST_FULL,
};

struct ListStruct;
struct ListNodeStruct;
struct DListStruct;
struct DListNodeStruct;

typedef struct ListStruct {
    size_t element_size;
    Array nodes;
    size_t len;
    struct ListNodeStruct *used_nodes;
    struct ListNodeStruct *spare_nodes;
} List;

typedef struct ListNodeStruct {
    struct ListNodeStruct *prev;
    char *obj;
} ListNode;

typedef struct DListStruct {
    size_t element_size;
    Array nodes;
    size_t len;
    struct DListNodeStruct *used_nodes;
    struct DListNodeStruct *spare_nodes;
} DList;

typedef struct DListNodeStruct {
    struct DListNodeStruct *prev;
    struct DListNodeStruct *next;
    char *obj;
} DListNode;

void list_init(List *list, size_t element_size);
bool list_init_alloc(List *list, size_t element_size, size_t length,
                                                      Status *status);
bool list_new(List **list, size_t element_size, Status *status);
bool list_new_alloc(List **list, size_t element_size, size_t length,
                                                          Status *status);
bool list_ensure_capacity(List *list, size_t length, Status *status);
bool list_push(List *list, void **obj, Status *status);
bool list_pop(List *list, void **obj, Status *status);
bool list_iterate(List *list, ListNode **node, void **obj);
void list_clear(List *list);
void list_free(List *list);

void dlist_init(DList *dlist, size_t element_size);
bool dlist_init_alloc(DList *dlist, size_t element_size, size_t length,
                                                         Status *status);
bool dlist_new(DList **dlist, size_t element_size, Status *status);
bool dlist_new_alloc(DList **dlist, size_t element_size, size_t length,
                                                             Status *status);
bool dlist_ensure_capacity(DList *dlist, size_t length, Status *status);
bool dlist_push_head(DList *dlist, void **obj, Status *status);
bool dlist_push_tail(DList *dlist, void **obj, Status *status);
bool dlist_pop_head(DList *dlist, void **obj, Status *status);
bool dlist_pop_tail(DList *dlist, void **obj, Status *status);
bool dlist_iterate(DList *list, DListNode **node, void **obj);
void dlist_clear(DList *dlist);
void dlist_free(DList *dlist);

#endif

/* vi: set et ts=4 sw=4: */
