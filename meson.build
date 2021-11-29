project(
  'cbase',
  'c',
  version : '0',
  default_options : ['c_std=c99', 'warning_level=3']
)

version = '0'
dependencies = []

conf_data = configuration_data()
conf_data.set('version', version)

incdirs = [include_directories('src')]

compiler = meson.get_compiler('c')

# if compiler.has_argument('-march=native')
#   add_global_arguments('-march=native', language : 'c')
# endif
if compiler.has_argument('-fsigned-char')
  add_global_arguments('-fsigned-char', language : 'c')
endif
if compiler.has_argument('-fwrapv')
  add_global_arguments('-fwrapv', language : 'c')
endif
if compiler.has_argument('-Wconversion')
  add_global_arguments('-Wconversion', language : 'c')
endif
if compiler.has_argument('-Wno-sign-conversion')
  add_global_arguments('-Wno-sign-conversion', language : 'c')
endif
if compiler.has_argument('-Wmissing-format-attribute')
  add_global_arguments('-Wmissing-format-attribute', language : 'c')
endif
if compiler.has_argument('-Wpointer-arith')
  add_global_arguments('-Wpointer-arith', language : 'c')
endif
if compiler.has_argument('-Winit-self')
  add_global_arguments('-Winit-self', language : 'c')
endif
if compiler.has_argument('-Wwrite-strings')
  add_global_arguments('-Wwrite-strings', language : 'c')
endif
if compiler.has_argument('-Wshadow')
  add_global_arguments('-Wshadow', language : 'c')
endif
if compiler.has_argument('-Wenum-compare')
  add_global_arguments('-Wenum-compare', language : 'c')
endif
if compiler.has_argument('-Wempty-body')
  add_global_arguments('-Wempty-body', language : 'c')
endif
if compiler.has_argument('-Wparentheses')
  add_global_arguments('-Wparentheses', language : 'c')
endif
if compiler.has_argument('-Wcast-align')
  add_global_arguments('-Wcast-align', language : 'c')
endif
if compiler.has_argument('-Wstrict-aliasing')
  add_global_arguments('-Wstrict-aliasing', language : 'c')
endif
if compiler.has_argument('--pedantic-errors')
  add_global_arguments('--pedantic-errors', language : 'c')
endif

if compiler.get_id() == 'clang' and compiler.has_argument('-ferror-limit=0')
  add_global_arguments('-ferror-limit=0', language : 'c')
endif

if ['clang', 'gcc'].contains(meson.get_compiler('c').get_id())
  add_global_arguments('-D_GNU_SOURCE', language : 'c')
endif

# [TODO] reallocarray, recallocarray, freezero, and aligned allocs

conf_data.set('HAVE_MEMSET_S', compiler.has_function(
  'memset_s',
  prefix : '#include <string.h>'
))

conf_data.set('HAVE_EXPLICIT_BZERO', compiler.has_function(
  'explicit_bzero',
  prefix : '#include <string.h>;#include <strings.h>'
))

conf_data.set('HAVE_MEMMEM', compiler.has_function(
  'memmem',
  prefix : '#include <string.h>'
))

conf_data.set('HAVE_ASM_BYTEORDER_H', compiler.has_header('asm/byteorder.h'))
conf_data.set('HAVE_BYTESWAP_H', compiler.has_header('byteswap.h'))
conf_data.set('HAVE_SYS_TYPES_H', compiler.has_header('sys/types.h'))
conf_data.set('HAVE_SYS_STAT_H', compiler.has_header('sys/stat.h'))
conf_data.set('HAVE_SYS_WAIT_H', compiler.has_header('sys/wait.h'))
conf_data.set('HAVE_UNISTD_H', compiler.has_header('unistd.h'))

have_format_function_attribute = compiler.has_function_attribute('format')
conf_data.set(
  'HAVE_FORMAT_FUNCTION_ATTRIBUTE',
  have_format_function_attribute
)

have_unused_function_attribute = compiler.has_function_attribute('unused')
conf_data.set(
  'HAVE_UNUSED_FUNCTION_ATTRIBUTE',
  have_unused_function_attribute
)

have_flatten_function_attribute = compiler.has_function_attribute('flatten')
conf_data.set(
  'HAVE_FLATTEN_FUNCTION_ATTRIBUTE',
  have_flatten_function_attribute
)

have_noinline_function_attribute = compiler.has_function_attribute('noinline')
conf_data.set(
  'HAVE_NOINLINE_FUNCTION_ATTRIBUTE',
  have_noinline_function_attribute
)

have_malloc_function_attribute = compiler.has_function_attribute('malloc')
conf_data.set(
  'HAVE_MALLOC_FUNCTION_ATTRIBUTE',
  have_malloc_function_attribute
)

have_nonnull_function_attribute = compiler.has_function_attribute('nonnull')
conf_data.set(
  'HAVE_NONNULL_FUNCTION_ATTRIBUTE',
  have_nonnull_function_attribute
)

have_returns_nonnull_function_attribute = (
  compiler.has_function_attribute('returns_nonnull')
)
conf_data.set(
  'HAVE_RETURNS_NONNULL_FUNCTION_ATTRIBUTE',
  have_returns_nonnull_function_attribute
)

have_warn_unused_result_function_attribute = (
  compiler.has_function_attribute('warn_unused_result')
)
conf_data.set(
  'HAVE_WARN_UNUSED_RESULT_FUNCTION_ATTRIBUTE',
  have_warn_unused_result_function_attribute
)

int_size = compiler.sizeof('int')
long_size = compiler.sizeof('long')
size_size = compiler.sizeof('size_t')
pointer_size = compiler.sizeof('intptr_t', prefix : '#include <stdint.h>')
maxint_size = compiler.sizeof('intmax_t', prefix : '#include <stdint.h>')
int128_size = compiler.sizeof('__int128')

if int_size == 2
  conf_data.set('HAVE_16BIT_INTS', true)
elif int_size != 4
  error('"int" must be either 16 or 32 bits')
endif

if long_size == 4
  conf_data.set('HAVE_32BIT_LONGS', true)
elif long_size != 8
  error('"long" must be either 32 or 64 bits')
endif

if size_size == 4
  conf_data.set('HAVE_32BIT_SIZES', true)
elif size_size != 8
  error('"size_t" must be either 32 or 64 bits')
endif

if pointer_size == 4
  conf_data.set('HAVE_32BIT_POINTERS', true)
elif pointer_size != 8
  error('"intptr_t" must be either 32 or 64 bits')
endif

if maxint_size == 4
  conf_data.set('HAVE_32BIT_MAXINTS', true)
elif maxint_size != 8
  error('"intmax_t" must be either 32 or 64 bits')
endif

if int128_size == 16
  conf_data.set('HAVE_128BIT_INTEGERS', true)
else
  conf_data.set('HAVE_128BIT_INTEGERS', false)
endif

inlining = get_option('inlining')

if inlining == 'CBASE_FLATTEN_FUNCTIONS'
  if not have_flatten_function_attribute
    warning('Cannot flatten functions without the flatten function attribute')
  endif

  if not have_unused_function_attribute
    warning(
      'Cannot mark static inline functions unused without the unused ' +
      'function attribute'
    )
  endif
elif inlining == 'CBASE_INLINE_FUNCTIONS'
  if not have_unused_function_attribute
    warning(
      'Cannot mark static inline functions unused without the unused ' +
      'function attribute'
    )
  endif
elif inlining == 'CBASE_NEVER_INLINE_FUNCTIONS'
  if not have_noinline_function_attribute
    warning('Cannot disable inlining without the noinline function attribute')
  endif
endif

if inlining == 'CBASE_FLATTEN_FUNCTIONS' and not have_flatten_function_attribute
  warning('Cannot flatten functions without the flatten function attribute')
endif

conf_data.set('CBASE_INLINING', inlining)

conf_data.set(
  'CBASE_DUMP_LOGGING_ERRORS_TO_STDERR',
  get_option('dump_logging_errors_to_stderr')
)

default_logger = get_option('default_logger')
default_logger_log_level = get_option('default_logger_log_level')

if default_logger_log_level == '' and not default_logger
  error(
    'Cannot set the default logger\'s log level without enabling the ' +
    'default log'
  )
endif

conf_data.set('CBASE_DEFAULT_LOGGER', get_option('default_logger'))
if default_logger_log_level == 'CBASE_LOG_LEVEL_RUNTIME'
  conf_data.set('CBASE_DEFAULT_LOGGER_LOG_LEVEL', default_logger_log_level)
else
  conf_data.set('CBASE_DEFAULT_LOGGER_LOG_LEVEL', default_logger_log_level)
endif

internal_logger = get_option('internal_logger')
internal_logger_log_level = get_option('internal_logger_log_level')

if internal_logger == 'CBASE_LOG_DEFAULT' and default_logger == ''
  error(
    'Cannot set the internal logger to output to the default log without ' +
    'enabling the default log'
  )
endif

if internal_logger_log_level == 'CBASE_LOG_DEFAULT' and internal_logger != ''
  error(
    'Cannot set the internal logger\'s log level when outputting to the ' +
    'default log'
  )
endif

if internal_logger_log_level != '' and internal_logger == ''
  error(
    'Cannot set the internal logger\'s log level without enabling the ' +
    'internal log'
  )
endif

conf_data.set('CBASE_INTERNAL_LOGGER', internal_logger)

if internal_logger_log_level == 'CBASE_LOG_LEVEL_RUNTIME'
  conf_data.set('CBASE_INTERNAL_LOGGER_LOG_LEVEL', internal_logger_log_level)
else
  conf_data.set('CBASE_INTERNAL_LOGGER_LOG_LEVEL', internal_logger_log_level)
endif

logger = get_option('logger')
logger_log_level = get_option('logger_log_level')

if logger == 'CBASE_LOG_DEFAULT' and default_logger == ''
  error(
    'Cannot set the logger to output to the default log without enabling ' +
    'the default log'
  )
endif

if logger_log_level == 'CBASE_LOG_DEFAULT' and logger != ''
  error(
    'Cannot set the logger\'s log level when outputting to the default log'
  )
endif

if logger_log_level != '' and logger == ''
  error('Cannot set the logger\'s log level without enabling the logger')
endif

conf_data.set('CBASE_LOGGER', logger)

if logger_log_level == 'CBASE_LOG_LEVEL_RUNTIME'
  conf_data.set('CBASE_LOGGER_LOG_LEVEL', logger_log_level)
else
  conf_data.set('CBASE_LOGGER_LOG_LEVEL', logger_log_level)
endif

if get_option('error_handling') != '' and internal_logger == ''
  error('Cannot enable error handling without the internal logger')
endif

conf_data.set('CBASE_ERRORS', get_option('error_handling'))

conf_data.set(
  'CBASE_DISABLE_INDEX_BOUNDS_CHECKS',
  get_option('disable_index_bounds_checks')
)

conf_data.set(
  'CBASE_DISABLE_LENGTH_BOUNDS_CHECKS',
  get_option('disable_length_bounds_checks')
)

conf_data.set(
  'CBASE_DISABLE_INDEXED_LENGTH_BOUNDS_CHECKS',
  get_option('disable_indexed_length_bounds_checks')
)

conf_data.set(
  'CBASE_DISABLE_OVERLAPPING_MEMORY_CHECKS',
  get_option('disable_overlapping_memory_corruption_checks')
)

conf_data.set(
  'CBASE_DISABLE_INPUT_OBJECT_POINTER_CHECKS',
  get_option('disable_input_object_argument_pointer_checks')
)

conf_data.set(
  'CBASE_DISABLE_INPUT_ARGUMENT_POINTER_CHECKS',
  get_option('disable_input_argument_pointer_checks')
)

conf_data.set(
  'CBASE_DISABLE_OUTPUT_POINTER_CHECKS',
  get_option('disable_output_argument_pointer_checks')
)

conf_data.set(
  'CBASE_DISABLE_CHECKED_MATH',
  get_option('disable_checked_math')
)

conf_data.set(
  'CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS',
  get_option('disable_checked_math_in_allocations')
)

conf_data.set(
  'CBASE_DISABLE_POINTER_ARITHMETIC_CHECKS',
  get_option('disable_pointer_arithmetic_checks')
)

configure_file(
  input : 'cbase_config.h.in',
  output : 'cbase_config.h',
  configuration : conf_data
)

add_global_arguments('-DCBASE_HAVE_CONFIG_H', language : 'c')

if compiler.has_function('iconv_open')
elif compiler.has_header_symbol('iconv.h', 'iconv_open')
  dependencies += compiler.find_library('iconv')
else
  error('Could not find iconv')
endif

utf8proc_dep = dependency('utf8proc', fallback : ['utf8proc', 'utf8proc_dep'])

dependencies += utf8proc_dep

cbase_src = [
  'src/alloc.c',
  'src/charset.c',
  'src/errors.c',
  'src/log.c',
  'src/str.c',
  'src/utf8.c',
  'src/util.c',
  'src/xxhash.c',
]

cbase_test_src = [
  'test/alloc.c',
  'test/array.c',
  'test/dlist.c',
  'test/list.c',
  'test/main.c',
  'test/str.c',
  'test/table.c',
  'test/utf8.c',
]

lib = library(
  'cbase',
  cbase_src,
  version : version,
  soversion : version,
  install : true,
  dependencies : dependencies,
  include_directories : incdirs
)

dependencies += compiler.find_library('cmocka')

test_exe = executable(
  'cbase_test',
  cbase_src,
  cbase_test_src,
  install : false,
  dependencies : dependencies,
  include_directories : incdirs
)

test('cbase tests', test_exe)
