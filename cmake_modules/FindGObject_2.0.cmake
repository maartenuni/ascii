# - Try to find GObject_2.0
# Once done, this will define
#
#  GObject_2.0_FOUND - system has GObject_2.0
#  GObject_2.0_INCLUDE_DIRS - the GObject_2.0 include directories
#  GObject_2.0_LIBRARIES - link these to use GObject_2.0

include(LibFindMacros)

# Dependencies
libfind_package(GObject_2.0 Glib_2.0)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(PANGO_PKGCONF pango)

# Include dir
find_path(GObject_2.0_INCLUDE_DIR
    NAMES gobject/gobject.h
    PATHS ${PANGO_PKGCONF_INCLUDE_DIRS}
    )

# Finally the library itself
find_library(GObject_2.0_LIBRARY
    NAMES gobject-2.0
    PATHS ${GObject_2.0_PKGCONF_LIBRARY_DIRS}
    )

# Set the include dir variables and the libraries and let libfind_process do
# the rest.
# NOTE: Singular variables for this library, plural for libraries this this
# lib depends on.
set(GObject_2.0_PROCESS_INCLUDES GObject_2.0_INCLUDE_DIR
    glib-2.0_INCLUDE_DIRS
    )
set(GObject_2.0_PROCESS_LIBS GObject_2.0_LIBRARY
    glib-2.0_LIBRARIES
    )

libfind_process(GObject_2.0)
