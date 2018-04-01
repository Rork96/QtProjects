include(LibFindMacros)

libfind_pkg_check_modules(ZLIB_PKGCONF zlib)

find_path(ZLIB_INCLUDE_DIR
    NAMES zlib/zlib.h
    PATHS ${ZLIB_PKGCONF_INCLUDE_DIRS}
)

find_library(ZLIB_LIBRARY
    NAMES zlib
    PATHS ${ZLIB_PKGCONF_LIBRARY_DIRS}
)

set(ZLIB_PROCESS_INCLUDES ZLIB_INCLUDE_DIR)
set(ZLIB_PROCESS_LIBS ZLIB_LIBRARY)
libfind_process(ZLIB)
