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

static inline void dlist_node_push_head(DListNode **node_list,
                                        DListNode *node) {
    DListNode *head = *node_list;

    if (!head) {
        node->prev = node;
        node->next = node;
    }
    else {
        node->prev = head->prev;
        node->next = head;
        head->prev->next = node;
        head->prev = node;
    }

    *node_list = node;
}

static inline void dlist_node_push_tail(DListNode **node_list,
                                        DListNode *node) {
    DListNode *head = *node_list;

    if (!head) {
        node->prev = node;
        node->next = node;
        *node_list = node;
    }
    else {
        node->prev = head->prev;
        node->next = head;
        head->prev->next = node;
        head->prev = node;
        *node_list = head;
    }
}

static inline bool dlist_node_pop_head(DListNode **node_list,
                                       DListNode **node) {
    DListNode *head = *node_list;

    if (!head) {
        return false;
    }

    head->prev->next = head->next;
    head->next->prev = head->prev;

    head->prev = head;
    head->next = head;

    *node = head;

    return true;
}

static inline bool dlist_node_pop_tail(DListNode **node_list,
                                       DListNode **node) {
    DListNode *head = *node_list;

    if (!head) {
        return false;
    }

    DListNode *tail = head->prev;

    tail->prev->next = tail->next;
    tail->next->prev = tail->prev;

    tail->prev = tail;
    tail->next = tail;

    *node = tail;

    return true;
}

void list_init(List *list) {
    array_init(&list->nodes, sizeof(ListNode));
    list->len = 0;
    list->used_nodes = NULL;
    list->spare_nodes = NULL;
}

bool list_init_alloc(List *list, size_t length, Status *status) {
    list_init(list);
    return list_ensure_capacity(list, length, status);
}

bool list_new(List **new_list, Status *status) {
    List *list = cbmalloc(sizeof(List));

    if (!list) {
        return alloc_failure(status);
    }

    list_init(list);

    *new_list = list;

    return status_ok(status);
}

bool list_new_alloc(List **new_list, size_t length, Status *status) {
    List *list = cbmalloc(sizeof(List));

    if (!list) {
        return alloc_failure(status);
    }

    if (!list_init_alloc(list, length, status)) {
        return false;
    }

    *new_list = list;

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
            node->obj = NULL;

            if (!list->spare_nodes) {
                list->spare_nodes = node;
            }
        }
    }

    return status_ok(status);
}

bool list_push(List *list, void *obj, Status *status) {
    if (!list_ensure_capacity(list, list->len + 1, status)) {
        return false;
    }

    ListNode *node = list->spare_nodes;

    node->prev = list->used_nodes;
    node->obj = obj;

    if (!list->used_nodes) {
        list->used_nodes = node;
    }

    list->len++;

    return status_ok(status);
}

bool list_pop(List *list, void **obj, Status *status) {
    if (!list->used_nodes) {
        return list_empty(status);
    }

    ListNode *node = list->used_nodes;

    node->prev = list->spare_nodes;
    *obj = node->obj;

    if (!list->spare_nodes) {
        list->spare_nodes = node;
    }

    list->len--;

    return status_ok(status);
}

bool list_iterate(List *list, ListNode **node, void **obj) {
    ListNode *local_node = NULL;

    if (node) {
        local_node = (*node)->prev;
    }
    else {
        local_node = list->used_nodes;
    }

    if (local_node) {
        *node = local_node;
        *obj = local_node->obj;

        return true;
    }

    return false;
}

void list_free(List *list) {
    array_free(&list->nodes);
    list_init(list);
}

void dlist_init(DList *dlist) {
    array_init(&dlist->nodes, sizeof(DListNode));
    dlist->len = 0;
    dlist->used_nodes = NULL;
    dlist->spare_nodes = NULL;
}

bool dlist_init_alloc(DList *dlist, size_t length, Status *status) {
    dlist_init(dlist);
    return dlist_ensure_capacity(dlist, length, status);
}

bool dlist_new(DList **new_dlist, Status *status) {
    DList *dlist = cbmalloc(sizeof(DList));

    if (!dlist) {
        return alloc_failure(status);
    }

    dlist_init(dlist);

    *new_dlist = dlist;

    return status_ok(status);
}

bool dlist_new_alloc(DList **new_dlist, size_t length, Status *status) {
    DList *dlist = cbmalloc(sizeof(DList));

    if (!dlist) {
        return alloc_failure(status);
    }

    if (!dlist_init_alloc(dlist, length, status)) {
        return false;
    }

    *new_dlist = dlist;

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

            node->obj = NULL;
            dlist_node_push_head(&dlist->spare_nodes, node);
        }
    }

    return status_ok(status);
}

bool dlist_push_head(DList *dlist, void *obj, Status *status) {
    if (!dlist_ensure_capacity(dlist, dlist->len + 1, status)) {
        return false;
    }

    DListNode *node = NULL;

    if (!dlist_node_pop_head(&dlist->spare_nodes, &node)) {
        return dlist_full(status);
    }

    node->obj = obj;

    dlist_node_push_head(&dlist->used_nodes, node);

    return status_ok(status);
}

bool dlist_push_tail(DList *dlist, void *obj, Status *status) {
    if (!dlist_ensure_capacity(dlist, dlist->len + 1, status)) {
        return false;
    }

    DListNode *node = NULL;

    if (!dlist_node_pop_head(&dlist->spare_nodes, &node)) {
        return dlist_full(status);
    }

    node->obj = obj;

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
    DListNode *local_node = NULL;

    if (!node) {
        if (dlist->used_nodes) {
            local_node = dlist->used_nodes->prev;
        }
    }
    else if (local_node->prev != dlist->used_nodes) {
        local_node = (*node)->prev;
    }

    if (local_node) {
        *node = local_node;
        *obj = local_node->obj;

        return true;
    }

    return false;
}

void dlist_free(DList *dlist) {
    array_free(&dlist->nodes);
    dlist_init(dlist);
}

/* vi: set et ts=4 sw=4: */
