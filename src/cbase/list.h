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
    Array nodes;
    size_t len;
    struct ListNodeStruct *used_nodes;
    struct ListNodeStruct *spare_nodes;
} List;

typedef struct ListNodeStruct {
    struct ListNodeStruct *prev;
    void *obj;
} ListNode;

typedef struct DListStruct {
    Array nodes;
    size_t len;
    struct DListNodeStruct *used_nodes;
    struct DListNodeStruct *spare_nodes;
} DList;

typedef struct DListNodeStruct {
    struct DListNodeStruct *prev;
    struct DListNodeStruct *next;
    void *obj;
} DListNode;

void list_init(List *list);
bool list_init_alloc(List *list, size_t length, Status *status);
bool list_new(List **new_list, Status *status);
bool list_new_alloc(List **new_list, size_t length, Status *status);
bool list_ensure_capacity(List *list, size_t length, Status *status);
bool list_push(List *list, void *obj, Status *status);
bool list_pop(List *list, void **obj, Status *status);
bool list_iterate(List *list, ListNode **node, void **obj);
void list_free(List *list);

void dlist_init(DList *dlist);
bool dlist_init_alloc(DList *dlist, size_t length, Status *status);
bool dlist_new(DList **new_dlist, Status *status);
bool dlist_new_alloc(DList **new_dlist, size_t length, Status *status);
bool dlist_ensure_capacity(DList *dlist, size_t length, Status *status);
bool dlist_push_head(DList *dlist, void *obj, Status *status);
bool dlist_push_tail(DList *dlist, void *obj, Status *status);
bool dlist_pop_head(DList *dlist, void **obj, Status *status);
bool dlist_pop_tail(DList *dlist, void **obj, Status *status);
bool dlist_iterate(DList *list, DListNode **node, void **obj);
void dlist_free(DList *dlist);

#endif

/* vi: set et ts=4 sw=4: */