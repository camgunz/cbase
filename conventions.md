# Conventions

- Output parameters always succeed input parameters

- Data structures use `len` where other libraries/languages/platforms might use
  `size`, `count`, `length`, and so on.

- If a data structure contains encoded data (i.e. UTF-8), `len` refers to the
  number of encoded codepoints and `byte_len` refers to the number of bytes the
  encoding requires.  Note this does **not** include the terminating zero (if
  it exists).  This also applies to functions that may deal with both number of
  encoded codepoints and number of bytes.

- If a data structure or function contains/deals with both number of encoded
  codepoints and number of bytes, `len` always precedes `byte_len`.
