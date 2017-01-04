# cbase

I found myself reimplementing things over and over again, so I'm consolidating
them into this repo.  Currently:

- Data structures:
  - Byte buffer and slice
  - String (UTF-8) and slice
  - Array
  - Pointer array
  - Single/Double linked list
  - Hash table
- Unicode handling (utf8proc)
- Status
  - Augments C error handling by adding domains and error messages to error
    codes
- Logging (not full-featured, for statuses and debugging)

Planned:

- File handling
- Decimal arithmetic (mpdecimal)

## License

cbase is dual-licensed under the MIT License and the Apache Software License,
version 2.0.

## Testing and Verification

cbase strives towards 100% function test coverage.  Currently the tests cover
69% of functions and 63% of lines.  I estimate I can achieve 100% function
coverage and 90% line coverage without resorting to crazy things like injecting
allocation failures.

I use all the Clang sanitizers and ensure there are no compilation warnings.

## Dependencies

cbase requires mpdecimal and utf8proc.

## Threadsafety

None of these data structures are threadsafe.  I have vague plans to do this,
but in a separate project.

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
1. You store untrusted keys in a hash table

Again, this is **critical**!  Don't just increment `seed` either, hit
`/dev/urandom` or `CryptGenRandom` for it.  It's not the default to avoid
syscall overhead in the common case.

Failure to do this will result in unimaginable slowness.

## Statuses

I anticipate the most controversial aspect of cbase will be `Status`, which is
similar to exceptions but adds a (negligible) amount of calling overhead and
provides no unwrapping.

Originally cbase used `int` error codes like most other C libraries.  However,
this led to inconsistent APIs in places.

For example: a `find` function should return `size_t` because indices can only
be positive, but a problem arises in the event a value is **not** found,
because no valid index can be returned.  The classic resolution of this issue
is to return `int` and then use negative values to indicate failure, however,
that's unsatisfactory because it limits your data structures to 31 bits of
length instead of 64 (you could argue that arrays shouldn't be this large, but
an array of `2 << 34` bits in length is easy to imagine).  You could even use
`ssize_t` and get up to `2 << 63`, but that's still only half of the potential
length.  For a more in-depth discussion, search for the semi-predicate problem.

`int` error codes also lack information about the module in which the error
occurred.  Data structures often depend on each other, i.e. hash tables and
arrays.  If a hash table's underlying array returns an error when reallocating,
the hash table has to map that error code to its own "allocation failed" error
code, but then callers aren't entirely sure where that allocation failure came
from.  Was it in hash table or array?  Does the hash table itself allocate?

This leads to the next point: `int` status codes are insufficient for tracing
errors to their source.  `Status` can track the file and line number of an
error; `int` is simply not capable of this.

Finally, `Status` can be handled via the provided macros.  The `Status` API
provides the ability to set handlers for any returned status.  This is most
helpful for allocation failures, which are typically due to fragmented or
exhausted memory, but there are other uses.

I initially wanted `Status` functionality for applications, but when writing
these data structures I saw that it could be useful for them as well.
