# - Try to find Pango
# Once done, this will define
#
#  Pango_FOUND - system has Pango
#  Pango_INCLUDE_DIRS - the Pango include directories
#  Pango_LIBRARIES - link these to use Pango

include(LibFindMacros)

# Dependencies
libfind_package(Pango Glib_2.0)
libfind_package(Pango GObject_2.0)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(PANGO_PKGCONF pango)

# Include dir
find_path(Pango_INCLUDE_DIR
    NAMES pango/pango.h
    PATHS ${PANGO_PKGCONF_INCLUDE_DIRS}
    )

# Finally the library itself
find_library(Pango_LIBRARY
    NAMES pango-1.0
    PATHS ${Pango_PKGCONF_LIBRARY_DIRS}
    )

# Set the include dir variables and the libraries and let libfind_process do
# the rest.
# NOTE: Singular variables for this library, plural for libraries this this
# lib depends on.
set(Pango_PROCESS_INCLUDES Pango_INCLUDE_DIR
    glib-2.0_INCLUDE_DIRS
    gobject-2.0_INCLUDE_DIRS
    )
set(Pango_PROCESS_LIBS Pango_LIBRARY
    glib-2.0_LIBRARIES
    gobject-2.0_LIBRARIES
    )
libfind_process(Pango)
