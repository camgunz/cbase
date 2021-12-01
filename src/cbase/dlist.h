#pragma once

#ifndef _CBASE_DLIST_H__
#define _CBASE_DLIST_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/array.h"

enum
{
    CBASE_DLIST_EMPTY = 24000,
    CBASE_DLIST_FULL,
};

#define CBASE_DLIST_DECL(_api, _dltype, _dlname, _otype)                      \
    struct _dltype##NodeStruct;                                               \
                                                                              \
    typedef struct _dltype##NodeStruct {                                      \
        struct _dltype##NodeStruct *prev;                                     \
        struct _dltype##NodeStruct *next;                                     \
        _otype obj;                                                           \
    } _dltype##Node;                                                          \
                                                                              \
    CBASE_ARRAY_DEF(_api,                                                     \
                    _dltype##NodeArray,                                       \
                    _dlname##_node_array,                                     \
                    _dltype##Node)                                            \
                                                                              \
    typedef struct _dltype##Struct {                                          \
        _dltype##NodeArray nodes;                                             \
        size_t len;                                                           \
        _dltype##Node *used_nodes;                                            \
        _dltype##Node *spare_nodes;                                           \
    } _dltype;

#define CBASE_DLIST_IMPL(_api, _dltype, _dlname, _otype)                      \
    _api CBASE_TMPL_API void _##_dlname##_node_push_tail(                     \
        _dltype##Node **node_list,                                            \
        _dltype##Node *node) {                                                \
        if (!(*node_list)) {                                                  \
            *node_list = node;                                                \
            node->prev = node;                                                \
            node->next = node;                                                \
        }                                                                     \
        else {                                                                \
            node->prev = (*node_list)->prev;                                  \
            node->next = (*node_list);                                        \
            (*node_list)->prev->next = node;                                  \
            (*node_list)->prev = node;                                        \
        }                                                                     \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _##_dlname##_node_push_head(                     \
        _dltype##Node **node_list,                                            \
        _dltype##Node *node) {                                                \
        _##_dlname##_node_push_tail(node_list, node);                         \
                                                                              \
        *node_list = node;                                                    \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _##_dlname##_node_pop_head(                       \
        _dltype##Node **node_list,                                            \
        _dltype##Node **node) {                                               \
        CBASE_ERROR_IF((!(*node_list)), CBASE_DLIST_EMPTY);                   \
                                                                              \
        *node = (*node_list);                                                 \
                                                                              \
        (*node_list)->prev->next = (*node_list)->next;                        \
        (*node_list)->next->prev = (*node_list)->prev;                        \
                                                                              \
        *node_list = (*node_list)->next;                                      \
                                                                              \
        (*node)->prev = (*node);                                              \
        (*node)->next = (*node);                                              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _##_dlname##_node_pop_tail(                       \
        _dltype##Node **node_list,                                            \
        _dltype##Node **node) {                                               \
        CBASE_ERROR_IF((!(*node_list)), CBASE_DLIST_EMPTY);                   \
                                                                              \
        *node = (*node_list)->prev;                                           \
                                                                              \
        (*node_list)->prev->prev->next = (*node_list)->prev->next;            \
        (*node_list)->prev->next->prev = (*node_list)->prev->prev;            \
                                                                              \
        (*node)->prev = (*node);                                              \
        (*node)->next = (*node);                                              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_ensure_capacity(_dltype *dlist,         \
                                                      size_t length) {        \
        size_t saved_alloc = dlist->nodes.alloc;                              \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dlname##_node_array_ensure_capacity(&dlist->nodes, length));     \
                                                                              \
        dlist->nodes.len = dlist->nodes.alloc;                                \
                                                                              \
        for (size_t i = saved_alloc; i < dlist->nodes.alloc; i++) {           \
            _dltype##Node *node =                                             \
                _dlname##_node_array_index_fast(&dlist->nodes, i);            \
                                                                              \
            _##_dlname##_node_push_head(&dlist->spare_nodes, node);           \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_init(_dltype *dlist) {                 \
        _dlname##_node_array_init(&dlist->nodes);                             \
        dlist->len = 0;                                                       \
        dlist->used_nodes = NULL;                                             \
        dlist->spare_nodes = NULL;                                            \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_init_alloc(_dltype *dlist,              \
                                                 size_t length) {             \
        _dlname##_init(dlist);                                                \
        return _dlname##_ensure_capacity(dlist, length);                      \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_new(_dltype **dlist) {                  \
        CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(_dltype), dlist));           \
                                                                              \
        _dlname##_init(*dlist);                                               \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_new_alloc(_dltype **dlist,              \
                                                size_t length) {              \
        CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(_dltype), dlist));           \
                                                                              \
        CBASE_PROPAGATE_ERROR(_dlname##_init_alloc(*dlist, length));          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_push_head_slot(_dltype *dlist,          \
                                                     _otype **obj) {          \
        CBASE_PROPAGATE_ERROR(                                                \
            _dlname##_ensure_capacity(dlist, dlist->len + 1));                \
                                                                              \
        _dltype##Node *node = NULL;                                           \
                                                                              \
        CBASE_ERROR_IF(_##_dlname##_node_pop_head(&dlist->spare_nodes,        \
                                                  &node),                     \
                       CBASE_DLIST_FULL);                                     \
                                                                              \
        _##_dlname##_node_push_head(&dlist->used_nodes, node);                \
                                                                              \
        *obj = &node->obj;                                                    \
                                                                              \
        dlist->len++;                                                         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_push_tail_slot(_dltype *dlist,          \
                                                     _otype **obj) {          \
        CBASE_PROPAGATE_ERROR(                                                \
            _dlname##_ensure_capacity(dlist, dlist->len + 1));                \
                                                                              \
        _dltype##Node *node = NULL;                                           \
                                                                              \
        CBASE_ERROR_IF(_##_dlname##_node_pop_head(&dlist->spare_nodes,        \
                                                  &node),                     \
                       CBASE_DLIST_FULL);                                     \
                                                                              \
        _##_dlname##_node_push_tail(&dlist->used_nodes, node);                \
                                                                              \
        *obj = &node->obj;                                                    \
                                                                              \
        dlist->len++;                                                         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_pop_head(_dltype *dlist,                \
                                               _otype **obj) {                \
        _dltype##Node *node = NULL;                                           \
                                                                              \
        CBASE_ERROR_IF(_##_dlname##_node_pop_head(&dlist->used_nodes, &node), \
                       CBASE_DLIST_EMPTY);                                    \
                                                                              \
        _##_dlname##_node_push_head(&dlist->spare_nodes, node);               \
                                                                              \
        dlist->len--;                                                         \
                                                                              \
        *obj = &node->obj;                                                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _dlname##_pop_tail(_dltype *dlist,                \
                                               _otype **obj) {                \
        _dltype##Node *node = NULL;                                           \
                                                                              \
        CBASE_ERROR_IF(_##_dlname##_node_pop_tail(&dlist->used_nodes, &node), \
                       CBASE_DLIST_EMPTY);                                    \
                                                                              \
        _##_dlname##_node_push_head(&dlist->spare_nodes, node);               \
                                                                              \
        dlist->len--;                                                         \
                                                                              \
        *obj = &node->obj;                                                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API bool _dlname##_iterate(_dltype *dlist,                \
                                               _dltype##Node **node,          \
                                               _otype **obj) {                \
        if (!*node) {                                                         \
            *node = dlist->used_nodes;                                        \
        }                                                                     \
        else {                                                                \
            *node = (*node)->next;                                            \
                                                                              \
            if (*node == dlist->used_nodes) {                                 \
                return false;                                                 \
            }                                                                 \
        }                                                                     \
                                                                              \
        if (!*node) {                                                         \
            return false;                                                     \
        }                                                                     \
                                                                              \
        *obj = &(*node)->obj;                                                 \
                                                                              \
        return true;                                                          \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_clear_no_zero(_dltype *dlist) {        \
        _dlname##_node_array_clear_no_zero(&dlist->nodes);                    \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_clear(_dltype *dlist) {                \
        _dlname##_node_array_clear(&dlist->nodes);                            \
        dlist->len = 0;                                                       \
        dlist->used_nodes = NULL;                                             \
        dlist->spare_nodes = NULL;                                            \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_free_no_zero(_dltype *dlist) {         \
        _dlname##_node_array_free_no_zero(&dlist->nodes);                     \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_free(_dltype *dlist) {                 \
        _dlname##_node_array_free(&dlist->nodes);                             \
        dlist->len = 0;                                                       \
        dlist->used_nodes = NULL;                                             \
        dlist->spare_nodes = NULL;                                            \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_destroy_no_zero(_dltype **dlist) {     \
        _dlname##_node_array_free_no_zero(&(*dlist)->nodes);                  \
        cbfree(*dlist);                                                       \
                                                                              \
        *dlist = NULL;                                                        \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _dlname##_destroy(_dltype **dlist) {             \
        _dlname##_node_array_free(&(*dlist)->nodes);                          \
        cbfree(*dlist);                                                       \
                                                                              \
        *dlist = NULL;                                                        \
    }

#define CBASE_DLIST_DEF(_dltype, _dlname, _otype)                             \
    CBASE_DLIST_DECL(_dltype, _dlname, _otype)                                \
    CBASE_DLIST_IMPL(_dltype, _dlname, _otype)

#endif
