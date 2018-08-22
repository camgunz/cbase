# To Do

## Features

- It would be nice to have an analog to `status_ok`, something like
  `status_pass_up` that essentially returns `false`, but may also call a status
  handler.  The main thing this provides is some kind of stack trace
  capability, but I'm a little worried in general about status handlers.  The
  implications for concurrency are a little daunting, and cbase provides no
  help there.

## Bugs

- `string_slice` should take units of codepoints like everything else (save
  `string_ensure_capacity`), not bytes.

## Benchmarks

- Devise some benchmarks
- Find some other libs...?
  - GLib
  - APR
  - hash table libraries
  - sds

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
- Decimals

## Docs

- cldoc

## Misc.

- statuses should also have a `func` field
- `*_free` functions need an accompanying `*_zero_free` that zeros the data
  before freeing it.  OpenBSD provides `freezero` and `recallocarray` for this
  kind of thing and should maybe be used if found; `recallocarray` is tricky
  though.

