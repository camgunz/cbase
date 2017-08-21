# cbase (not at all ready for production use)

cbase is an application library for C applications.  It provides:

- Data structures:
  - Byte buffer and slice
  - String (UTF-8) and slice
  - Array
  - Pointer array
  - Single/Double linked list
  - Hash table
- Decimal arithmetic (mpdecimal)
- Unicode handling (utf8proc)
- Charset converstion (libiconv)
- Byte swapping
- Path and file manipulation
- Status
  - Augments C error handling by adding domains and error messages to error
    codes
- Logging (not full-featured, for statuses and debugging)

## License

cbase is dual-licensed under either the MIT License or the Apache Software
License, Version 2.0.  Both are included here, in the [LICENSE](LICENSE) and
[LICENSE-APL20](LICENSE-APL20) files respectively.

## Testing

cbase strives towards 100% function test coverage.  Currently the tests cover
69% of functions and 63% of lines.  I estimate I can achieve 100% function
coverage and 80% line coverage without resorting to injecting failures.

I use all the Clang sanitizers and ensure there are no compilation warnings.

## Requirements

cbase requires:
- C99
- a C standard library
- dynamic allocation
- 32 or 64-bit architecture

## Dependencies

cbase depends on:
- [mpdecimal](http://www.bytereef.org/mpdecimal/)
- [utf8proc](https://julialang.org/utf8proc/)
- [libiconv](https://www.gnu.org/software/libiconv/)

## Thread Safety

cbase is thread aware, meaning that no errors will occur so long as structures
aren't shared across threads.

I'd like to write threadsafe, lock-free implementations and enable them with a
compile flag, but that is very far off.

## Hash Table

There's (thankfully, because I needed it) a lot of info on hash tables out
there these days.  This hash table uses:

- open addressing
- xxHash
- power-of-2 sizes
- Robin Hood hash collision resolution

Hash tables can also be seeded.  This is important (read: **critical**) in two
cases:

1. You plan on passing data between hash tables
2. You store untrusted keys in a hash table

In these cases, failure to seed will result in **unimaginable** slowness.
Don't just increment `seed` either, hit `/dev/urandom` or `CryptGenRandom` for
it.  It's not the default to avoid syscall overhead in the common case.

## Statuses

I anticipate the most controversial aspect of cbase will be `Status`, which is
similar to exceptions but adds a (negligible) amount of calling overhead and
provides no unwrapping.

Originally cbase used `int` error codes like most other C libraries.  However,
`int` error codes are subject to the
[semipredicate problem](https://en.wikipedia.org/wiki/Semipredicate_problem)
and this led to inconsistent APIs in places.

Further, `int` error codes lack information about where the error occured.
Data structures often depend on each other, i.e. hash tables and arrays/lists.
If a hash table's underlying array/list returns an error when reallocating, the
hash table has to map that error code to its own "allocation failed" error
code, but then callers aren't entirely sure where that allocation failure came
from.  Was it in hash table or array/list?  Does the hash table itself
allocate?  `Status` has a `domain` field, so in this case the `status->domain`
would be `array` (cbase's hash tables use arrays).

`int` error codes are also insufficient for tracing errors to their source.
`Status` has `file` and `line` fields for just this purpose.

Finally, `Status` can be handled via provided macros.  The `Status` API
provides the ability to set handlers for any returned status.  This is most
helpful for allocation failures -- typically due to fragmented or exhausted
memory -- but there are other uses.  However, exercise care when using this
feature.  Status handlers have some of the issues exceptions have, particularly
non-locality.  Ex:

```c
if (!call_a_function_that_returns_handled_status(&thing, status)) {
    /* Status handler ran here, but there's no way of knowing from this code */
    return definitely_nothing_ran(status);
}
```

### Status Performance

The performance burden of `Status` is very, very small.  Most cases are success
cases, in which case you incur:
  - Passing an extra pointer to a function
  - Returning a `bool`
  - Checking the value of the returned `bool`

Compared to `int` status codes:
  - Returning an `int`
  - Checking the value of the returned `int`

In the error case, `Status` is still relatively quick:
  - Passing an extra pointer to a function
  - Setting `status->level` (`enum`... `int` really)
  - Setting `status->domain` (`const char *`)
  - Setting `status->code` (`int`)
  - Setting `status->message` (`const char *`)
  - Setting `status->file` (`const char *`)
  - Setting `status->line` (`int`)
  - Returning a `bool`
  - Checking the value of the returned `bool`

## General Philosophy

### Security is the default

cbase's basic functions perform checks by default; usually these are bounds and
overflow checks.  cbase always checks return values and never swallows errors.

### Performance is possible

Where possible, cbase provides `_fast` variants of functions that bypass
checks.  For example, if you use `array_ensure_capacity`, you can then use
`array_index_fast` with confidence as long as your index is within the ensured
capacity.

### Consistency is paramount

cbase strives for consistency everywhere: naming, parameter order (counts
before sizes), style, and so on.
