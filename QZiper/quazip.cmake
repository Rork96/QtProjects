include(LibFindMacros)

libfind_pkg_check_modules(QUAZIP_PKGCONF quazip5)

find_path(QUAZIP_INCLUDE_DIR
    NAMES quazip5/quazip.h
    PATHS ${QUAZIP_PKGCONF_INCLUDE_DIRS}
)

find_library(QUAZIP_LIBRARY
    NAMES quazip
    PATHS ${QUAZIP_PKGCONF_LIBRARY_DIRS}
)

set(QUAZIP_PROCESS_INCLUDES QUAZIP_INCLUDE_DIR)
set(QUAZIP_PROCESS_LIBS QUAZIP_LIBRARY)
libfind_process(QUAZIP)
