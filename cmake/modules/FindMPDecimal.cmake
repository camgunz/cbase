INCLUDE(FindPackageHandleStandardArgs)

IF (NOT MPDECIMAL_INCLUDE_DIR)
    FIND_PATH(MPDECIMAL_INCLUDE_DIR mpdecimal.h HINTS $ENV{MPDECIMAL_DIR})
ENDIF()

IF (NOT MPDECIMAL_LIBRARIES)
    FIND_LIBRARY(MPDECIMAL_LIBRARIES mpdec HINTS $ENV{MPDECIMAL_DIR})
ENDIF()

MARK_AS_ADVANCED(MPDECIMAL_INCLUDE_DIR)
MARK_AS_ADVANCED(MPDECIMAL_LIBRARIES)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    MPDECIMAL
    DEFAULT_MSG
    MPDECIMAL_LIBRARIES
    MPDECIMAL_INCLUDE_DIR
)

