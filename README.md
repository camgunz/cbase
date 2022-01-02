# cbase (not at all ready for production use)

cbase is an application library for C applications. It provides:

- Data structures:
  - Raw data manipulation
  - Array and slice
  - Raw UTF-8 data manipulation
    - Unicode handling via utf8proc
  - String (UTF-8) and slice
  - Singly/Doubly linked list
  - Hash table
- Charset converstion via libiconv
- Byte swapping
- Logging (not full-featured, for errors and debugging)

## License

cbase is dual-licensed under either the MIT License or the Apache Software
License, Version 2.0. Both are included here, in the [LICENSE](LICENSE) and
[LICENSE-APL20](LICENSE-APL20) files respectively.

## Requirements

cbase requires:
- C99
- a C standard library
- dynamic allocation
- 32 or 64-bit architecture

## Dependencies

cbase depends on:
- [utf8proc](https://julialang.org/utf8proc/)
- [iconv](https://www.gnu.org/software/libiconv/)

Building cbase requires [meson](https://mesonbuild.com). We also use
[compdb](https://github.com/Sarcasm/compdb) to augment the
`compile_commands.json` file for development.

## General Philosophy

### Safety is the default

cbase performs extensive checking by default:
- All pointer arguments are checked for `NULL`
- All indexing and size arguments are bounds checked
- All addition/subtraction/multiplication operations are checked for overflow
- Any operation that might corrupt data via overlapping memory is checked

cbase always checks return values and never swallows errors.

### Performance is possible

Where possible, cbase provides `_no_check` variants of functions that bypass
checks. For example, if you use `array_ensure_capacity`, you can then use
`array_index_no_check` with confidence as long as your index is within the
ensured capacity.

It is also possible to configure cbase at compile time to not perform these
checks at all.

### Consistency is paramount

cbase strives for consistency everywhere: naming, parameter order (counts
before sizes, etc.), style, and so on.

## Testing

cbase strives towards 100% function test coverage. Currently the tests cover
69% of functions and 63% of lines. 100% function test coverage is planned, and
I estimate I can achieve 80% line coverage without resorting to injecting
failures.

I use all the Clang sanitizers and ensure there are no compilation warnings.

## Thread Safety

cbase is thread aware, meaning that no errors will occur so long as structures
aren't shared across threads.

## Hash Table

There's (thankfully, because I needed it) a lot of info on hash tables out
there these days. This hash table uses:

- open addressing
- xxHash
- power-of-2 sizes
- Robin Hood hash collision resolution

Hash tables can also be seeded. This is important (read: **critical**) in two
cases:

1. You plan on passing data between hash tables
2. You store untrusted keys in a hash table

In these cases, failure to seed will result in **unimaginable** slowness.
Don't just increment `seed` either; hit `/dev/urandom` or `CryptGenRandom` for
it. It's not the default to avoid syscall overhead in the common case.
