# To Do

## Next time

- Arrays
  - Use tests to find problems

## Big

- Reimplement utf8 and str
- Get list.h and dlist.h up to par

## Small

- Find all ` +` instances and wrap in `check_overflow` or something
- Find all ` -` instances that are pointer arithmetic, and replace it with
  `positive_ptrdiff`

- byte_len -> len in utf8
- Many `string_*` functions need fast variants based on their utf8 counterparts
- Expand `utf8_pop_*` to `pop_left` and `pop_right`
  - Build on this to `string_pop_*` to `pop_left` and `pop_right`
- Add `cstr` functions to str.h
- All `*_assign` functions should take ownership of their arguments
  - n.b. this doesn't make sense for slices
  - n.b. 2 `*_assign` for data and arrays is in `*_slice*.h`
- Ensure everything modifies their output parameters only on success
- Build checked 64-bit math functions that don't require 128-bits of precision

## Musings and dreams

- tables might benefit from having a local hasher?
- Parameterize string encoding
  - Not super clear on how to do this
- Consider adding an allocation size strategy for functions that auto-resize,
  i.e. `*_encode` or even `*_append_*`.  Currently it's "always double" which
  almost certainly non-optimal.
- Iterators
- `*_free` functions need an accompanying `*_zero_free` that zeros the data
  before freeing it.  OpenBSD provides `freezero` and `recallocarray` for this
  kind of thing and should maybe be used if found; `recallocarray` is tricky
  though.
- Switch table to https://github.com/martinus/robin-hood-hashing
- Function attributes:
  - GCC: `malloc`
  - GCC: `nonnull`
  - GCC: `access`
  - GCC: `assume_aligned`
  - GCC: `returns_nonnull`
  - GCC: `warn_unused_result`
  - GCC: `fallthrough`

## Benchmarks

- Other libs:
  - GLib
  - APR
  - hash table libraries
    - Look at https://github.com/attractivechaos/klib/
    - uthash
  - sds
  - libcperciva
  - Fraggle's C algorithms
  - tommyds
  - C++ STL
	- Ludocode's Pottery

## Tests

- Log
- Charset

## Docs

I think this will be hard because of the preprocessor-ness of things. But
current fave tool is `cldoc`.

## Add-on Library Ideas

- cbase-path/file/stream
  - Break this out
- cbase-mpfr
- cbase-gmp
- cbase-event
- cbase-json
- cbase-regex
- cbase-msgpack
