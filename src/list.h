#ifndef LIST_H__
#define LIST_H__

struct ListNodeStruct;
struct DListNodeStruct;

typedef struct ListNodeStruct {
    struct ListNodeStruct *next;
    void *obj;
} ListNode;

typedef struct DListNodeStruct {
    struct DListNodeStruct *prev;
    struct DListNodeStruct *next;
    void *obj;
    uint32_t hash;
} DListNode;

typedef struct {
    size_t len;
    ListNode *head;
    ListNode *tail;
} List;

typedef struct {
    size_t len;
    DListNode *head;
    DListNode *tail;
} DList;

void list_init(List *list);
bool list_new(List **new_list, Status *status);
bool list_prepend(List *list, void *obj, Status *status);
bool list_append(List *list, void *obj, Status *status);
bool list_pop_left(List *list, void **obj);

void       dlist_init(DList *dlist);
bool       dlist_new(DList **new_dlist, Status *status);
bool       dlist_prepend(DList *dlist, void *obj, Status *status);
void       dlist_prepend_node(DList *dlist, DListNode *node);
bool       dlist_append(DList *dlist, void *obj, Status *status);
void       dlist_append_node(DList *dlist, DListNode *node);
bool       dlist_pop_left(DList *dlist, void **obj);
bool       dlist_pop_right(DList *dlist, void **obj);
DListNode* dlist_find_node(DList *dlist, void *obj);
void       dlist_remove_node(DList *dlist, DListNode *node);
void       dlist_concat(DList *dl1, DList *dl2);

#endif

/* vi: set et ts=4 sw=4: */
