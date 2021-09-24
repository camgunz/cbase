# Deps

What's the point of deps?

If I want a static array, I need:
- static_array.h
  - static_data.h
    - mutable_data.h
      - data_slice.h
        - common_data.h
  - mutable_array.h
    - mutable_data.h
      - data_slice.h
        - common_data.h
    - array_slice.h
      - data_slice.h
        - common_data.h
      - common_array.h
        - common_data.h

Or, flattened:
static_array.h
static_data.h
mutable_data.h
data_slice.h
common_data.h
mutable_array.h
array_slice.h
common_array.h

So when I define CBASE_STATIC_ARRAY_IMPL, I have to specify:
- CBASE_STATIC_DATA_IMPL_NO_DEPS
- CBASE_MUTABLE_ARRAY_IMPL_NO_DEPS
- CBASE_MUTABLE_DATA_IMPL_NO_DEPS
- CBASE_ARRAY_SLICE_IMPL_NO_DEPS
- CBASE_DATA_SLICE_IMPL_NO_DEPS
- CBASE_COMMON_ARRAY_IMPL_NO_DEPS
- CBASE_COMMON_DATA_IMPL_NO_DEPS

But ideally I would only know about my immediate dependencies, so:
- CBASE_STATIC_DATA_IMPL_NO_DEPS (adjacent)
- CBASE_MUTABLE_ARRAY_IMPL (above)
