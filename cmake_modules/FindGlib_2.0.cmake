# - Try to find Glib_2.0
# Once done, this will define
#
#  Glib_2.0_FOUND - system has Glib_2.0
#  Glib_2.0_INCLUDE_DIRS - the Glib_2.0 include directories
#  Glib_2.0_LIBRARIES - link these to use Glib_2.0

include(LibFindMacros)

# Dependencies
# none

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(GLIB_2.0_PKGCONF glib-2.0)
message(STATUS "glib inc dirs = ${GLIB_2.0_PKGCONF_INCLUDE_DIRS}")
# Include dir
find_path(Glib_2.0_INCLUDE_DIR_1
    NAMES glib.h
    PATHS ${GLIB_2.0_PKGCONF_INCLUDE_DIRS}
    )
find_path(Glib_2.0_INCLUDE_DIR_2
    NAMES glibconfig.h
    PATHS ${GLIB_2.0_PKGCONF_INCLUDE_DIRS}
    )

set(Glib_2.0_INCLUDE_DIR "${Glib_2.0_INCLUDE_DIR_1};${Glib_2.0_INCLUDE_DIR_2}")

# Finally the library itself
find_library(Glib_2.0_LIBRARY
    NAMES glib-2.0
    PATHS ${Glib_2.0_PKGCONF_LIBRARY_DIRS}
    )

# Set the include dir variables and the libraries and let libfind_process do
# the rest.
# NOTE: Singular variables for this library, plural for libraries this this
# lib depends on.
set(Glib_2.0_PROCESS_INCLUDES Glib_2.0_INCLUDE_DIR)
set(Glib_2.0_PROCESS_LIBS Glib_2.0_LIBRARY)
libfind_process(Glib_2.0)
