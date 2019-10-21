# To Do

## General

- Array can't use `void *` for its elements because it breaks alignment for
  scalars.
- Bounds checking in `utf8.c`
- Paramterize string encoding
  - Not super clear on how to do this
- Add a better allocator; probably necessary to get competitive table
  performance.
- Wrap any function taking a `void **` with a macro to make the cast
- The `*_assign` functions should take ownership of their arguments
- Find functions that check if their output arguments are `NULL` and make
  alternative functions when possible
- Ensure everything besides `strbase` modifies their output parameters only on
  success
- Consider adding an allocation size strategy for functions that auto-resize,
  i.e. `*_encode` or even `*_append_*`.  Currently it's ad-hoc and almost
  certainly non-optimal.
- Iterators
- Add `*_no_zero` pop functions

## Benchmarks

- Other libs:
  - GLib
  - APR
  - hash table libraries
    - khash
    - uthash
  - sds
  - libcperciva
  - Fraggle's C algorithms
  - tommyds
  - C++ STL

## APIs

- Check for consistency, i.e. when accepting a length, should an error occur if
  len is longer than the data structure, or should it... clear, for example in
  the case of truncation.
  - Some functions are implicitly "do this is it's possible, otherwise I don't
    care", but the downside of that is that if you do care, you might end up
    performing the check twice -- once to do the check and once implicitly in
    the operation itself.  Some have "fast" variants but many don't.
  - I think the best thing is to push this into a naming convention... which I
    think should be `*_quiet`?

## Tests

- Buffer
  - Slice
- Log
- Charset
- Path

## Docs

- cldoc

## Misc.

- `*_free` functions need an accompanying `*_zero_free` that zeros the data
  before freeing it.  OpenBSD provides `freezero` and `recallocarray` for this
  kind of thing and should maybe be used if found; `recallocarray` is tricky
  though.

## Add-on Library Ideas

- cbase-mpfr
- cbase-gmp
- cbase-json
- cbase-regex
- cbase-msgpack
