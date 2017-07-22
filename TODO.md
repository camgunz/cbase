# To Do

## Misc.

- Development
  - File handling (?)
- "shrink" should become "compact"
- Add overflow checks

## Benchmarks

- Devise some benchmarks
- Find some other libs...?
  - GLib
  - APR
  - hash table libraries
  - sds

## APIs

- String could use some printfs
- Check for consistency, i.e. when accepting a length, should an error occur if
  len is longer than the data structure, or should it... clear, for example in
  the case of truncation.
- Anything `*Slice` can do, the underlying data structure should also be able
  to do.  Probably a lot of copy/paste, but so be it.

## Tests

- Buffer
  - Slice
- Log
- Status
- Alloc

## Docs

- Probably cldoc?
