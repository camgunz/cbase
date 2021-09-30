# Reorganization

## data_base.h

- index_no_check
- index
- slice_no_check
- slice
- copy_no_check
- copy
- equals_no_check
- equals
- starts_with_no_check
- starts_with
- ends_with_no_check
- ends_with
- find_no_check
- find

### data_slice_management.h

- assign_no_check
- assign

#### data_ownership_management.h

- ensure_capacity_no_zero
- ensure_capacity
- set_capacity_no_zero_no_check
- set_capacity_no_zero
- set_capacity_no_check
- set_capacity

#### data_static_management.h

- ensure_capacity_no_zero_no_check
- ensure_capacity_no_check
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

#### data_dynamic_management.h

- ensure_capacity_no_zero_no_check
- ensure_capacity_no_zero
- ensure_capacity_no_check
- ensure_capacity
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

### data_slice_mutations.h

- mutable_index_no_check
- mutable_index
- zero_no_check
- zero
- set_no_check
- set
- skip_no_check
- skip
- seek_no_check
- seek
- truncate_no_zero_no_check
- truncate_no_zero
- pop_left_no_zero_no_check
- pop_left_no_zero
- pop_right_no_zero_no_check
- pop_right_no_zero
- clear_no_zero_no_check
- clear_no_zero
- clear_no_check
- clear

### data_static_mutations.h

- truncate_no_check
- truncate
- compact_no_check
- compact
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

### data_dynamic_mutations.h

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
- replace_no_zero
- replace

## data.h

- data_base.h

## slice.h

- data_base.h
- data_slice_management.h

## mutable_slice.h

- data_base.h
- data_slice_management.h
- data_slice_mutations.h

## static_data.h

- data_base.h
- data_slice_management.h
- data_static_management.h

## mutable_static_data.h

- data_base.h
- data_slice_management.h
- data_static_management.h
- data_slice_mutations.h
- data_static_mutations.h

## mutable_dynamic_data.h

- data_base.h
- data_slice_management.h
- data_dynamic_management.h
- data_slice_mutations.h
- data_dynamic_mutations.h
