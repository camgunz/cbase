#include "cbase.h"

void list_init(List *list) {
    list->len = 0;
    list->head = NULL;
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

bool list_prepend(List *list, void *obj, Status *status) {
    ListNode *node = cbmalloc(sizeof(ListNode));

    if (!node) {
        return alloc_failure(status);
    }

    node->next = list->head;
    node->obj = obj;
    list->head = node;

    if (!list->tail) {
        list->tail = node;
    }

    list->len++;

    return status_ok(status);
}

bool list_append(List *list, void *obj, Status *status) {
    ListNode *node = cbmalloc(sizeof(ListNode));

    if (!node) {
        return alloc_failure(status);
    }

    node->next = NULL;
    node->obj = obj;
    if (list->tail) {
        list->tail->next = node;
    }

    return status_ok(status);
}

bool list_pop_left(List *list, void **obj) {
    ListNode *node = list->head;

    if (!node) {
        return false;
    }

    *obj = node->obj;

    list->head = node->next;

    list->len--;

    cbfree(node);

    return true;
}

void dlist_init(DList *dlist) {
    dlist->len = 0;
    dlist->head = NULL;
    dlist->tail = NULL;
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

bool dlist_prepend(DList *dlist, void *obj, Status *status) {
    DListNode *node = cbmalloc(sizeof(DListNode));

    if (!node) {
        return alloc_failure(status);
    }

    node->prev = NULL;
    node->next = dlist->head;
    node->obj = obj;
    node->hash = 0;
    dlist->head->prev = node;
    dlist->head = node;

    dlist->len++;

    return status_ok(status);
}

bool dlist_append(DList *dlist, void *obj, Status *status) {
    DListNode *node = cbmalloc(sizeof(DListNode));

    if (!node) {
        return alloc_failure(status);
    }

    node->prev = dlist->tail;
    node->next = NULL;
    node->obj = obj;
    node->hash = 0;
    dlist->tail->next = node;
    dlist->tail = node;

    dlist->len++;

    return status_ok(status);
}

bool dlist_pop_left(DList *dlist, void **obj) {
    DListNode *node = dlist->head;

    if (!node) {
        return false;
    }

    *obj = node->obj;

    dlist->head = node->next;
    dlist->head->prev = NULL;

    dlist->len--;

    cbfree(node);

    return true;
}

bool dlist_pop_right(DList *dlist, void **obj) {
    DListNode *node = dlist->tail;

    if (!node) {
        return false;
    }

    *obj = node->obj;
    dlist->tail = node->prev;
    dlist->tail->next = NULL;

    dlist->len--;

    cbfree(node);

    return true;
}

DListNode* dlist_find_node(DList *dlist, void *obj) {
    for (DListNode *node = dlist->head; node != NULL; node = node->next) {
        if (node->obj == obj) {
            return node;
        }
    }

    return NULL;
}

DListNode* dlist_find_node_reverse(DList *dlist, void *obj) {
    for (DListNode *node = dlist->tail; node != NULL; node = node->prev) {
        if (node->obj == obj) {
            return node;
        }
    }

    return NULL;
}

void dlist_remove_node(DList *dlist, DListNode *node) {
    if (node == dlist->head) {
        dlist->head = dlist->head->next;
    }

    if (node == dlist->tail) {
        dlist->tail = dlist->tail->prev;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;

    dlist->len--;
}

void dlist_concat(DList *dl1, DList *dl2) {
    dl2->head->prev = dl1->tail;
    dl1->tail->next = dl2->head;
    dl1->tail = dl2->tail;
    dl1->len += dl2->len;

    dlist_init(dl2);
}

/* vi: set et ts=4 sw=4: */
