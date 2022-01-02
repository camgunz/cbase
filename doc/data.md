# Data

## Static data

Static data is data that doesn't change capacity. Its maximum capacity is
defined at compile time, and cannot be changed. Static data owns its memory,
and if allocated on the heap, it will deallocate the data as well.

Static data has a current size and a maximum capacity. As data is added, the
size increases. If an operation would ever cause the size to exceed the maximum
capacity, it results in `CBASE_ERROR_OUT_OF_BOUNDS`.

## Dynamic data

Dynamic data is data that can change capacity. Dynamic data owns its memory,
and if allocated on the heap, it will deallocate the data as well.

Dynamic data has a current size and a maximum capacity. As data is added, the
size increases. If an operation would ever cause the size to exceed the maximum
capacity, it reallocates and expands the capacity before performing the
operation.

## Data slice

A data slice is data that references some other data. It can be resized, though
since it does not keep track of its original reference, take care not to resize
it past its underlying allocation. Data slices do not own their memory, and
will become invalid if the underlying allocation is freed.

Data slices have a start pointer and a size. They can be mutable, but their
mutation operations are restricted to those that would never modify the
underlying allocation's size such that it might exhaust the remaining capacity.
This is a limitation relative to static and dynamic data.

On the other hand, data slices have an ability that static and dynamic data
don't: they can modify their start pointer. This allows slices to easily move
through data.

## Mutable data

As alluded to above, any of static data, dynamic data, or a data slice can be
mutable if specified at compile time. Mutability refers to the data itself, not
the data structure--immutable data structures can be resized, reassigned, etc.

Further, cbase's "immutability" simply means there is no API for mutating the
data. It is of course possible to do so without using cbase. To avoid this,
employ the `const` modifier.
