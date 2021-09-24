# Data and arrays

## common_data

### Functions

- index_no_check
- index
- slice_no_check
- slice
- copy_no_check
- copy
- truncate_no_check
- truncate
- equals_no_check
- equals
- starts_with_no_check
- starts_with
- ends_with_no_check
- ends_with
- find_no_check
- find
- clear_no_check
- clear

## data_slice

### Functions

- assign_no_check
- assign
- skip_no_check
- skip
- seek_no_check
- seek
- pop_left_no_zero_no_check
- pop_left_no_zero
- pop_right_no_zero_no_check
- pop_right_no_zero

### Deps

CBASE_COMMON_DATA_IMPL

## mutable_data

### Functions

- mutable_index_no_check
- mutable_index
- zero_no_check
- zero
- ensure_capacity_no_zero_no_check
- ensure_capacity_no_zero
- ensure_capacity_no_check
- ensure_capacity
- set_capacity_no_zero_no_check
- set_capacity_no_zero
- set_capacity_no_check
- set_capacity
- set_no_check
- set
- truncate_no_check
- truncate
- compact_no_check
- compact
- move_right_no_zero_no_check
- move_right_no_zero
- move_right_no_check
- move_right
- move_left_no_zero_no_check
- move_left_no_zero
- move_left_no_check
- move_left
- insert_slot_no_zero_no_check
- insert_slot_no_zero
- insert_slot_no_check
- insert_slot
- insert_no_check
- insert
- prepend_slot_no_zero_no_check
- prepend_slot_no_zero
- prepend_slot_no_check
- prepend_slot
- prepend_no_check
- prepend
- append_slot_no_zero_no_check
- append_slot_no_zero
- append_slot_no_check
- append_slot
- append_no_check
- append
- delete_no_zero_no_check
- delete_no_zero
- delete_no_check
- delete
- delete_until_no_zero_no_check
- delete_until_no_zero
- delete_until_no_check
- delete_until
- delete_unordered_no_zero_no_check
- delete_unordered_no_zero
- delete_unordered_no_check
- delete_unordered
- replace_no_zero
- replace
- pop_no_zero_no_check
- pop_no_zero
- pop_no_check
- pop
- pop_unordered_no_zero_no_check
- pop_unordered_no_zero
- pop_unordered_no_check
- pop_unordered
- pop_left_no_check
- pop_left
- pop_left_unordered_no_check
- pop_left_unordered
- pop_right_no_check
- pop_right
- clear_no_check
- clear

### Deps

CBASE_DATA_SLICE_IMPL
*CBASE_DATA_SLICE_IMPL_DEPS & CBASE_DATA_SLICE_IMPL_NO_DEPS*

## static_data

### Functions

- init_no_check
- init
- init_from_data_no_check
- init_from_data
- free_no_zero_no_check
- free_no_zero
- free_no_check
- free
- destroy_no_zero_no_check
- destroy_no_zero
- destroy_no_check
- destroy

### Deps

CBASE_MUTABLE_DATA_IMPL
*CBASE_MUTABLE_DATA_IMPL_DEPS & CBASE_MUTABLE_DATA_IMPL_NO_DEPS*

## dynamic_data

### Functions

- init_no_check
- init
- init_capacity_no_check
- init_capacity
- init_from_data_no_check
- *init_from_data*
- free_no_zero_no_check
- free_no_zero
- free_no_check
- free
- destroy_no_zero_no_check
- destroy_no_zero
- destroy_no_check
- destroy

### Deps

CBASE_MUTABLE_DATA_IMPL
*CBASE_MUTABLE_DATA_IMPL_DEPS & CBASE_MUTABLE_DATA_IMPL_NO_DEPS*

## common_array

### Functions

- index_no_check
- index
- slice_no_check
- slice
- copy_no_check
- copy
- truncate_no_check
- truncate
- equals_no_check
- equals
- starts_with_no_check
- starts_with
- ends_with_no_check
- ends_with
- find_no_check
- find
- clear_no_check
- clear

## array_slice

### Functions

- assign_no_check
- assign
- skip_no_check
- skip
- seek_no_check
- seek
- pop_left_no_zero_no_check
- pop_left_no_zero
- pop_right_no_zero_no_check
- pop_right_no_zero

### Deps

CBASE_DATA_SLICE_IMPL_NO_DEPS
CBASE_COMMON_ARRAY_IMPL

## mutable_data

### Functions

- mutable_index_no_check
- mutable_index
- zero_no_check
- zero
- ensure_capacity_no_zero_no_check
- ensure_capacity_no_zero
- ensure_capacity_no_check
- ensure_capacity
- set_capacity_no_zero_no_check
- set_capacity_no_zero
- set_capacity_no_check
- set_capacity
- set_no_check
- set
- truncate_no_check
- truncate
- compact_no_check
- compact
- move_right_no_zero_no_check
- move_right_no_zero
- move_right_no_check
- move_right
- move_left_no_zero_no_check
- move_left_no_zero
- move_left_no_check
- move_left
- insert_slot_no_zero_no_check
- insert_slot_no_zero
- insert_slot_no_check
- insert_slot
- insert_no_check
- insert
- prepend_slot_no_zero_no_check
- prepend_slot_no_zero
- prepend_slot_no_check
- prepend_slot
- prepend_no_check
- prepend
- append_slot_no_zero_no_check
- append_slot_no_zero
- append_slot_no_check
- append_slot
- append_no_check
- append
- delete_no_zero_no_check
- delete_no_zero
- delete_no_check
- delete
- delete_until_no_zero_no_check
- delete_until_no_zero
- delete_until_no_check
- delete_until
- delete_unordered_no_zero_no_check
- delete_unordered_no_zero
- delete_unordered_no_check
- delete_unordered
- replace_no_zero
- replace
- pop_no_zero_no_check
- pop_no_zero
- pop_no_check
- pop
- pop_unordered_no_zero_no_check
- pop_unordered_no_zero
- pop_unordered_no_check
- pop_unordered
- pop_left_no_check
- pop_left
- pop_left_unordered_no_check
- pop_left_unordered
- pop_right_no_check
- pop_right
- clear_no_check
- clear

### Deps

CBASE_DATA_SLICE_IMPL
*CBASE_DATA_SLICE_IMPL_DEPS & CBASE_DATA_SLICE_IMPL_NO_DEPS*

## static_data

### Functions

- init_no_check
- init
- init_from_data_no_check
- init_from_data
- free_no_zero_no_check
- free_no_zero
- free_no_check
- free
- destroy_no_zero_no_check
- destroy_no_zero
- destroy_no_check
- destroy

### Deps

CBASE_MUTABLE_DATA_IMPL
*CBASE_MUTABLE_DATA_IMPL_DEPS & CBASE_MUTABLE_DATA_IMPL_NO_DEPS*

## dynamic_data

### Functions

- init_no_check
- init
- init_capacity_no_check
- init_capacity
- init_from_data_no_check
- *init_from_data*
- free_no_zero_no_check
- free_no_zero
- free_no_check
- free
- destroy_no_zero_no_check
- destroy_no_zero
- destroy_no_check
- destroy

### Deps

CBASE_MUTABLE_DATA_IMPL
*CBASE_MUTABLE_DATA_IMPL_DEPS & CBASE_MUTABLE_DATA_IMPL_NO_DEPS*
