INCLUDE(FindPackageHandleStandardArgs)

IF (NOT ICONV_INCLUDE_DIR)
    FIND_PATH(ICONV_INCLUDE_DIR iconv.h HINTS $ENV{ICONV_DIR})
ENDIF()

IF (NOT ICONV_LIBRARIES)
    CHECK_FUNCTION_EXISTS("iconv" ICONV_IN_LIBC)
    IF(ICONV_IN_LIBC)
        SET(ICONV_LIBRARIES "c")
    ELSE()
        FIND_LIBRARY(ICONV_LIBRARIES iconv HINTS $ENV{ICONV_DIR})
    ENDIF()
ENDIF()

MARK_AS_ADVANCED(ICONV_INCLUDE_DIR)
MARK_AS_ADVANCED(ICONV_LIBRARIES)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    Iconv
    DEFAULT_MSG
    ICONV_LIBRARIES
    ICONV_INCLUDE_DIR
)