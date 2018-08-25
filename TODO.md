# To Do

## General

- Remove decimal support
  - There should be an associated library (named, say, cbase-mpfr) that
    essentially wraps the calls using `Status`.
- Bounds checking in `utf8.c`
- Paramterize string encoding
  - Not super clear on how to do this
- Add a better allocator; probably necessary to get competitive table
  performance.
- Wrap any function taking a `void **` with a macro to make the cast

## Consistency

cbase currently contains several inconsistencies, which are documented here as
the first step towards resolving them.

### NULL output parameters

Some functions handle `NULL` output parameters and don't write to them, but
many don't.  Rather than branching to check if they're `NULL` though, I think
there should just be different functions.

### Using output parameters internally

Most functions only modify output parameters on success, but a few don't follow
this rule.  This probably makes sense for `strbase`, which is more or less
internal, but everything else should follow the rule.

### `ptrdiff_t`

`ptrdiff_t` is probably a bad idea in general; it's better to check for
potential "whoops that's actually behind" and then use `size_t` to avoid
overflow.  Might merit a macro/util function.

### `status_propagate`

`status_propagate` was recently added and not everything's switched over.  This
might also merit a macro or something in the status module.

## Benchmarks

- Devise some benchmarks
- Find some other libs...?
  - GLib
  - APR
  - hash table libraries
    - khash
    - uthash
  - sds
  - libcperciva
  - tommyds
  - C++ STL

## APIs

- Check for consistency, i.e. when accepting a length, should an error occur if
  len is longer than the data structure, or should it... clear, for example in
  the case of truncation.

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

