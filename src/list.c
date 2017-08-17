#include "cbase.h"

#define list_empty(status) status_failure( \
    status,                                \
    "list",                                \
    LIST_EMPTY,                            \
    "List is empty"                        \
)

#define dlist_empty(status) status_failure( \
    status,                                 \
    "dlist",                                \
    DLIST_EMPTY,                            \
    "DList is empty"                        \
)

#define dlist_full(status) status_failure( \
    status,                                \
    "dlist",                               \
    DLIST_FULL,                            \
    "DList is full"                        \
)

static inline void dlist_node_push_tail(DListNode **node_list,
                                        DListNode *node) {
    if (!(*node_list)) {
        *node_list = node;
        node->prev = node;
        node->next = node;
    }
    else {
        node->prev = (*node_list)->prev;
        node->next = (*node_list);
        (*node_list)->prev->next = node;
        (*node_list)->prev = node;
    }
}

static inline void dlist_node_push_head(DListNode **node_list,
                                        DListNode *node) {
    dlist_node_push_tail(node_list, node);

    *node_list = node;
}

static inline bool dlist_node_pop_head(DListNode **node_list,
                                       DListNode **node) {
    if (!(*node_list)) {
        return false;
    }

    *node = (*node_list);

    (*node_list)->prev->next = (*node_list)->next;
    (*node_list)->next->prev = (*node_list)->prev;

    *node_list = (*node_list)->next;

    (*node)->prev = (*node);
    (*node)->next = (*node);

    return true;
}

static inline bool dlist_node_pop_tail(DListNode **node_list,
                                       DListNode **node) {
    if (!(*node_list)) {
        return false;
    }

    *node = (*node_list)->prev;

    (*node_list)->prev->prev->next = (*node_list)->prev->next;
    (*node_list)->prev->next->prev = (*node_list)->prev->prev;

    (*node)->prev = (*node);
    (*node)->next = (*node);

    return true;
}

void list_init(List *list, size_t element_size) {
    list->element_size = element_size;
    array_init(&list->nodes, sizeof(ListNode) + element_size);
    list->len = 0;
    list->used_nodes = NULL;
    list->spare_nodes = NULL;
}

bool list_init_alloc(List *list, size_t element_size, size_t length,
                                                      Status *status) {
    list_init(list, element_size);
    return list_ensure_capacity(list, length, status);
}

bool list_new(List **list, size_t element_size, Status *status) {
    if (!cbmalloc(1, sizeof(List), (void **)list, status)) {
        return false;
    }

    list_init(list, element_size);

    return status_ok(status);
}

bool list_new_alloc(List **list, size_t element_size, size_t length,
                                                      Status *status) {
    if (!cbmalloc(1, sizeof(List), (void **)list, status)) {
        return false;
    }

    if (!list_init_alloc(list, element_size, length, status)) {
        return false;
    }

    return status_ok(status);
}

bool list_ensure_capacity(List *list, size_t length, Status *status) {
    size_t saved_len = list->nodes.len;

    if (!array_ensure_capacity(&list->nodes, length, status)) {
        return false;
    }

    list->nodes.len = list->nodes.alloc;

    if (list->nodes.len > saved_len) {
        for (size_t i = saved_len; i < list->nodes.len; i++) {
            ListNode *node = (ListNode *)array_index_fast(&list->nodes, i);

            node->prev = list->spare_nodes;
            node->obj = ((char *)node) + sizeof(ListNode);
            list->spare_nodes = node;
        }
    }

    return status_ok(status);
}

bool list_push(List *list, void **obj, Status *status) {
    if (!list_ensure_capacity(list, list->len + 1, status)) {
        return false;
    }

    ListNode *node = list->spare_nodes;

    list->spare_nodes = node->prev;
    node->prev = list->used_nodes;
    *obj = node->obj;
    list->used_nodes = node;

    list->len++;

    return status_ok(status);
}

bool list_pop(List *list, void **obj, Status *status) {
    if (!list->used_nodes) {
        return list_empty(status);
    }

    ListNode *node = list->used_nodes;

    list->used_nodes = node->prev;
    node->prev = list->spare_nodes;
    *obj = node->obj;
    list->spare_nodes = node;

    list->len--;

    return status_ok(status);
}

bool list_iterate(List *list, ListNode **node, void **obj) {
    if (!*node) {
        *node = list->used_nodes;
    }
    else {
        *node = (*node)->prev;
    }

    if (!*node) {
        return false;
    }

    *obj = (*node)->obj;

    return true;
}

void list_free(List *list) {
    array_free(&list->nodes);
    list_init(list, list->element_size);
}

void dlist_init(DList *dlist, size_t element_size) {
    dlist->element_size = element_size;
    array_init(&dlist->nodes, sizeof(DListNode) + element_size);
    dlist->len = 0;
    dlist->used_nodes = NULL;
    dlist->spare_nodes = NULL;
}

bool dlist_init_alloc(DList *dlist, size_t element_size, size_t length,
                                                         Status *status) {
    dlist_init(dlist, element_size);
    return dlist_ensure_capacity(dlist, length, status);
}

bool dlist_new(DList **dlist, size_t element_size, Status *status) {
    if (!cbmalloc(1, sizeof(DList), (void **)dlist, status)) {
        return false;
    }

    dlist_init(dlist, element_size);

    return status_ok(status);
}

bool dlist_new_alloc(DList **dlist, size_t element_size, size_t length,
                                                         Status *status) {
    if (!cbmalloc(1, sizeof(DList), (void **)dlist, status)) {
        return false;
    }

    if (!dlist_init_alloc(dlist, element_size, length, status)) {
        return false;
    }

    return status_ok(status);
}

bool dlist_ensure_capacity(DList *dlist, size_t length, Status *status) {
    size_t saved_len = dlist->nodes.len;

    if (!array_ensure_capacity(&dlist->nodes, length, status)) {
        return false;
    }

    dlist->nodes.len = dlist->nodes.alloc;

    if (dlist->nodes.len > saved_len) {
        for (size_t i = saved_len; i < dlist->nodes.len; i++) {
            DListNode *node = (DListNode *)array_index_fast(&dlist->nodes, i);

            dlist_node_push_head(&dlist->spare_nodes, node);
            node->obj = ((char *)node) + sizeof(DListNode);
        }
    }

    return status_ok(status);
}

bool dlist_push_head(DList *dlist, void **obj, Status *status) {
    if (!dlist_ensure_capacity(dlist, dlist->len + 1, status)) {
        return false;
    }

    DListNode *node = NULL;

    if (!dlist_node_pop_head(&dlist->spare_nodes, &node)) {
        return dlist_full(status);
    }

    *obj = node->obj;

    dlist_node_push_head(&dlist->used_nodes, node);

    return status_ok(status);
}

bool dlist_push_tail(DList *dlist, void **obj, Status *status) {
    if (!dlist_ensure_capacity(dlist, dlist->len + 1, status)) {
        return false;
    }

    DListNode *node = NULL;

    if (!dlist_node_pop_head(&dlist->spare_nodes, &node)) {
        return dlist_full(status);
    }

    *obj = node->obj;

    dlist_node_push_tail(&dlist->used_nodes, node);

    return status_ok(status);
}

bool dlist_pop_head(DList *dlist, void **obj, Status *status) {
    DListNode *node = NULL;

    if (!dlist_node_pop_head(&dlist->used_nodes, &node)) {
        return dlist_empty(status);
    }

    dlist_node_push_head(&dlist->spare_nodes, node);

    *obj = node->obj;

    return status_ok(status);
}

bool dlist_pop_tail(DList *dlist, void **obj, Status *status) {
    DListNode *node = NULL;

    if (!dlist_node_pop_tail(&dlist->used_nodes, &node)) {
        return dlist_empty(status);
    }

    dlist_node_push_head(&dlist->spare_nodes, node);

    *obj = node->obj;

    return status_ok(status);
}

bool dlist_iterate(DList *dlist, DListNode **node, void **obj) {
    if (!*node) {
        *node = dlist->used_nodes;
    }
    else {
        *node = (*node)->next;

        if (*node == dlist->used_nodes) {
            return false;
        }
    }

    if (!*node) {
        return false;
    }

    *obj = (*node)->obj;

    return true;
}

void dlist_free(DList *dlist) {
    array_free(&dlist->nodes);
    dlist_init(dlist, dlist->element_size);
}

/* vi: set et ts=4 sw=4: */
