#pragma once

#ifndef ASTR_H__
#define ASTR_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "cbase/errors.h"
#include "cbase/charset.h"
#include "cbase/array_slice.h"
#include "cbase/utf8.h"
#include "cbase/util.h"

SLICEABLE_ARRAY_DEF(String, string, SSlice, sslice, char)

int   string_ensure_capacity(String *array, size_t len);
int   string_ensure_capacity_zero(String *array, size_t len);

int   string_set_size(String *array, size_t len);

int   string_compact(String *array);

char* string_index_fast(String *array, size_t index);
int   string_index(String *array, size_t index, char **element);

void  string_zero_data_fast(String *array, size_t index,
                                              size_t count);
int   string_zero_data(String *array, size_t index, size_t count);
void  string_zero_element_fast(String *array, size_t index);
int   string_zero_element(String *array, size_t index);

void  string_set_fast(String *array, size_t index, const char *element);
int   string_set(String *array, size_t index, const char *element);
void  string_set_many_fast(String *array, size_t index, const char *data,
                                                       size_t count);
int   string_set_many(String *array, size_t index, const char *data,
                                                 size_t count);
void  string_set_string_fast(String *dst, size_t index, String *src);
int   string_set_string (String *dst, size_t index, String *src);

void  string_truncate_fast(String *array, size_t len);
int   string_truncate_no_zero(String *array, size_t len);
int   string_truncate(String *array, size_t len);

void  string_assign_fast(String *array, const char *data, size_t count);
int   string_assign(String *array, const char *data, size_t count);
void  string_assign_string_fast(String *dst, String *src);
int   string_assign_string (String *dst, String *src);

void  string_init(String *array);
int   string_init_alloc(String *array, size_t count);
int   string_init_alloc_zero(String *array, size_t count);
int   string_init_from_data(String *array, const char *data, size_t len);

int   string_new(String **array);
int   string_new_alloc(String **array, size_t count);
int   string_new_alloc_zero(String **array, size_t count);
int   string_new_from_data(String **array, const char *data, size_t len);

bool  string_equals_data_at_fast(String *array, size_t index, const char *data,
                                                              size_t len);
int   string_equals_data_at(String *array, size_t index, const char *data,
                                                         size_t len,
                                                         bool *equal);
bool  string_equals_data(String *array, const char *data, size_t len);
bool  string_equals_array(String *b1, String *b2);

bool  string_starts_with_data_fast(String *array, const char *data, size_t len);
bool  string_starts_with_data(String *array, const char *data, size_t len,
                                                               bool *equal);

bool  string_ends_with_data_fast(String *array, const char *data, size_t len);
int   string_ends_with_data(String *array, const char *data, size_t len,
                                                             bool *equal);

void  string_shift_data_right_fast_no_zero(String *array, size_t index,
                                                          size_t count);
void  string_shift_data_right_fast(String *array, size_t index, size_t count);
int   string_shift_data_right_no_zero(String *array, size_t index,
                                                     size_t count);
int   string_shift_data_right(String *array, size_t index, size_t count);

void  string_shift_data_left_fast_no_zero(String *array, size_t index,
                                                         size_t count);
void  string_shift_data_left_fast(String *array, size_t index, size_t count);
int   string_shift_data_left_no_zero(String *array, size_t index,
                                                    size_t count);
int   string_shift_data_left(String *array, size_t index, size_t count);

void  string_insert_fast(String *array, size_t index, char *element);
int   string_insert(String *array, size_t index, char *element);
char* string_insert_slot_fast_no_zero(String *array, size_t index);
char* string_insert_slot_fast(String *array, size_t index);
int   string_insert_slot_no_zero(String *array, size_t index, char **new_slot);
int   string_insert_slot(String *array, size_t index, char **new_slot);
void  string_insert_many_fast(String *array, size_t index, const char *data,
                                                           size_t count);
int   string_insert_many(String *array, size_t index, const char *data,
                                                      size_t count);
void  string_insert_string_fast(String *dst, size_t index, String *src);
int   string_insert_string (String *dst, size_t index, String *src);

void  string_prepend_fast(String *array, char *element);
int   string_prepend(String *array, char *element);
char* string_prepend_slot_fast(String *array);
int   string_prepend_slot(String *array, char **new_slot);
int   string_prepend_slot_no_zero(String *array, char **new_slot);
int   string_prepend_many(String *array, const char *data, size_t count);
void  string_prepend_many_fast(String *array, const char *data, size_t count);
void  string_prepend_string_fast(String *dst, String *src);
int   string_prepend_string (String *dst, String *src);

void  string_append_fast(String *array, char *element);
int   string_append(String *array, char *element);
char* string_append_slot_fast_no_zero(String *array);
char* string_append_slot_fast(String *array);
int   string_append_slot_no_zero(String *array, char **new_slot);
int   string_append_slot(String *array, char **new_slot);
void  string_append_many_fast(String *array, const char *data, size_t count);
int   string_append_many(String *array, const char *data, size_t count);
void  string_append_string_fast(String *dst, String *src);
int   string_append_string (String *dst, String *src);

void  string_delete_many_fast_no_zero(String *array, size_t index, size_t count);
void  string_delete_many_fast(String *array, size_t index, size_t count);
int   string_delete_many_no_zero(String *array, size_t index, size_t count);
int   string_delete_many(String *array, size_t index, size_t count);
void  string_delete_fast(String *array, size_t index);
int   string_delete_no_zero(String *array, size_t index);
int   string_delete(String *array, size_t index);
void  string_delete_unordered_fast_no_zero(String *array, size_t index);
void  string_delete_unordered_fast(String *array, size_t index);
int   string_delete_unordered_no_zero(String *array, size_t index);
int   string_delete_unordered(String *array, size_t index);

void  string_copy_data_fast(String *array, size_t index, size_t count,
                                                         char *data);
int   string_copy_data(String *array, size_t index, size_t count, char *data);
void  string_copy_element_fast(String *array, size_t index, char *element);
int   string_copy_element(String *array, size_t index, char *element);

void  string_pop_fast_no_zero(String *array, size_t index, char *element);
void  string_pop_fast(String *array, size_t index, char *element);
int   string_pop_no_zero(String *array, size_t index, char *element);
int   string_pop(String *array, size_t index, char *element);

void  string_pop_unordered_fast_no_zero(String *array, size_t index,
                                                       char *element);
void  string_pop_unordered_fast(String *array, size_t index, char *element);
int   string_pop_unordered_no_zero(String *array, size_t index, char *element);
int   string_pop_unordered(String *array, size_t index, char *element);

void  string_pop_left_fast(String *array, char *element);
int   string_pop_left(String *array, char *element);
void  string_pop_left_unordered_fast(String *array, char *element);
int   string_pop_left_unordered(String *array, char *element);

void  string_pop_right_fast(String *array, char *element);
int   string_pop_right(String *array, char *element);
void  string_pop_right_unordered_fast(String *array, char *element);
int   string_pop_right_unordered(String *array, char *element);

void  string_clear_no_zero(String *array);
void  string_clear(String *array);

void  string_free_no_zero(String *array);
void  string_free(String *array);

void  string_destroy_no_zero(String **array);
void  string_destroy(String **array);

void  string_assign_slice_fast(String *array, SSlice *slice);
int   string_assign_slice(String *array, SSlice *slice);

void  string_slice_fast(String *array, size_t index, size_t len, SSlice *slice);
int   string_slice(String *array, size_t index, size_t len, SSlice *slice);
void  string_slice_full(String *array, SSlice *slice);

void  string_insert_slice_fast(String *array, size_t index, SSlice *slice);
int   string_insert_slice(String *array, size_t index, SSlice *slice);

void  string_prepend_slice_fast(String *array, SSlice *slice);
int   string_prepend_slice(String *array, SSlice *slice);

void  string_append_slice_fast(String *array, SSlice *slice);
int   string_append_slice(String *array, SSlice *slice);

void  string_set_slice_fast(String *array, size_t index, SSlice *slice);
int   string_set_slice(String *array, size_t index, SSlice *slice);

void string_assign_utf8_cstr_fast(String *string, const char *cs) {
    string_assign_fast(string, cs, strlen(cs));
}

int string_assign_utf8_cstr(String *string, const char *cs) {
    return string_assign(string, cs, strlen(cs));
}

int string_init_from_cstr(String *string, const char *cs) {
    string_init(string);
    return string_assign_utf8_cstr(string, cs);
}

int string_new_from_cstr(String **string, const char *cs) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_cstr(*string, cs),
        cbfree,
        *string
    );

    return 0;
}

void  sslice_truncate_fast(SSlice *slice, size_t len);
int   sslice_truncate(SSlice *slice, size_t len);

bool  sslice_equals_data_at_fast(SSlice *slice, size_t index,
                                                size_t len,
                                                const char *data);
int   sslice_equals_data_at(SSlice *slice, size_t index, size_t len,
                                                         const char *data,
                                                         bool *equal);

bool  sslice_equals_data(SSlice *slice, const char *data);
bool  sslice_equals(SSlice *s1, SSlice *s2);

bool  sslice_starts_with_data_fast(SSlice *slice, const char *data,
                                                  size_t len);
int   sslice_starts_with_data(SSlice *slice, const char *data, size_t len,
                                                               bool *equal);

bool  sslice_ends_with_data_fast(SSlice *slice, const char *data, size_t len);
int   sslice_ends_with_data(SSlice *slice, const char *data, size_t len,
                                                             bool *equal);

void  sslice_copy_data_fast(SSlice *slice, size_t index, size_t len,
                                                         char *out);
bool  sslice_copy_data(SSlice *slice, size_t index, size_t len, char *out);

void  sslice_pop_left_fast(SSlice *slice, char *element);
int   sslice_pop_left(SSlice *slice, char *element);

void  sslice_pop_right_fast(SSlice *slice, char *element);
int   sslice_pop_right(SSlice *slice, char *element);

void  sslice_skip_fast(SSlice *slice, size_t count);
int   sslice_skip(SSlice *slice, size_t count);

void  sslice_seek_to_data_fast(SSlice *slice, const char *data);
int   sslice_seek_to_data(SSlice *slice, const char *data);

void  sslice_clear(SSlice *slice);

#endif

/* vi: set et ts=4 sw=4: */
