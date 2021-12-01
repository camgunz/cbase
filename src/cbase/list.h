#pragma once

#ifndef _CBASE_LIST_H__
#define _CBASE_LIST_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/array.h"

enum
{
    CBASE_LIST_EMPTY = 23000,
    CBASE_LIST_FULL,
};

#define CBASE_LIST_DECL(_api, _ltype, _lname, _otype)                         \
    struct _ltype##NodeStruct;                                                \
                                                                              \
    typedef struct _ltype##NodeStruct {                                       \
        struct _ltype##NodeStruct *next;                                      \
        _otype obj;                                                           \
    } _ltype##Node;                                                           \
                                                                              \
    CBASE_ARRAY_DEF(_api,                                                     \
                    _ltype##NodeArray,                                        \
                    _lname##_node_array,                                      \
                    _ltype##Node)                                             \
                                                                              \
    typedef struct _ltype##Struct {                                           \
        _ltype##NodeArray nodes;                                              \
        size_t len;                                                           \
        _ltype##Node *used_nodes;                                             \
        _ltype##Node *spare_nodes;                                            \
    } _ltype;

#define CBASE_LIST_IMPL(_api, _ltype, _lname, _otype)                         \
    _api CBASE_TMPL_API int _lname##_ensure_capacity(_ltype *list,            \
                                                     size_t length) {         \
        size_t saved_alloc = list->nodes.alloc;                               \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _lname##_node_array_ensure_capacity(&list->nodes, length));       \
                                                                              \
        list->nodes.len = list->nodes.alloc;                                  \
                                                                              \
        for (size_t i = saved_alloc; i < list->nodes.alloc; i++) {            \
            _ltype##Node *node =                                              \
                _lname##_node_array_index_fast(&list->nodes, i);              \
                                                                              \
            node->next = list->spare_nodes;                                   \
            list->spare_nodes = node;                                         \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _lname##_init(_ltype *list) {                    \
        _lname##_node_array_init(&list->nodes);                               \
        list->len = 0;                                                        \
        list->used_nodes = NULL;                                              \
        list->spare_nodes = NULL;                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _lname##_init_alloc(_ltype *list,                 \
                                                size_t length) {              \
        _lname##_init(list);                                                  \
        return _lname##_ensure_capacity(list, length);                        \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _lname##_new(_ltype **list) {                     \
        CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(_ltype), list));             \
                                                                              \
        _lname##_init(*list);                                                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _lname##_new_alloc(_ltype **list,                 \
                                               size_t length) {               \
        CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(_ltype), list));             \
                                                                              \
        CBASE_PROPAGATE_ERROR(_lname##_init_alloc(*list, length));            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _lname##_push_slot(_ltype *list, _otype **obj) {  \
        CBASE_PROPAGATE_ERROR(_lname##_ensure_capacity(list, list->len + 1)); \
                                                                              \
        CBASE_ERROR_IF((!(list->spare_nodes)), CBASE_LIST_EMPTY);             \
                                                                              \
        _ltype##Node *node = list->spare_nodes;                               \
        list->spare_nodes = node->next;                                       \
                                                                              \
        node->next = list->used_nodes;                                        \
        list->used_nodes = node;                                              \
        list->len++;                                                          \
                                                                              \
        *obj = &node->obj;                                                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API int _lname##_pop(_ltype *list, _otype **obj) {        \
        CBASE_ERROR_IF(!list->used_nodes, CBASE_LIST_EMPTY);                  \
                                                                              \
        _ltype##Node *node = list->used_nodes;                                \
        list->used_nodes = node->next;                                        \
                                                                              \
        node->next = list->spare_nodes;                                       \
        list->spare_nodes = node;                                             \
        list->len--;                                                          \
                                                                              \
        *obj = &node->obj;                                                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API bool _lname##_iterate(_ltype *list,                   \
                                              _ltype##Node **node,            \
                                              _otype **obj) {                 \
        if (!*node) {                                                         \
            *node = list->used_nodes;                                         \
        }                                                                     \
        else {                                                                \
            *node = (*node)->next;                                            \
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
    _api CBASE_TMPL_API void _lname##_clear_no_zero(_ltype *list) {           \
        _lname##_node_array_clear_no_zero(&list->nodes);                      \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _lname##_clear(_ltype *list) {                   \
        _lname##_node_array_clear(&list->nodes);                              \
        list->len = 0;                                                        \
        list->used_nodes = NULL;                                              \
        list->spare_nodes = NULL;                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _lname##_free_no_zero(_ltype *list) {            \
        _lname##_node_array_free_no_zero(&list->nodes);                       \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _lname##_free(_ltype *list) {                    \
        _lname##_node_array_free(&list->nodes);                               \
        list->len = 0;                                                        \
        list->used_nodes = NULL;                                              \
        list->spare_nodes = NULL;                                             \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _lname##_destroy_no_zero(_ltype **list) {        \
        _lname##_node_array_free_no_zero(&(*list)->nodes);                    \
        cbfree(*list);                                                        \
                                                                              \
        *list = NULL;                                                         \
    }                                                                         \
                                                                              \
    _api CBASE_TMPL_API void _lname##_destroy(_ltype **list) {                \
        _lname##_node_array_free(&(*list)->nodes);                            \
        cbfree(*list);                                                        \
                                                                              \
        *list = NULL;                                                         \
    }

#define CBASE_LIST_DEF(_ltype, _lname, _otype)                                \
    CBASE_LIST_DECL(_ltype, _lname, _otype)                                   \
    CBASE_LIST_IMPL(_ltype, _lname, _otype)

#endif
