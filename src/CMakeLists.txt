
set(ASCII_FUN_SOURCES
        ascii-fun.cpp
        ascii-generators.cpp
        CharacterStats.cpp
        FontConfigEnumerator.cpp
        FontUtils.cpp
        GlyphRenderer.cpp
        init-libs.cpp
        PangoUtils.cpp
        )

set(ASCII_FUN_HEADERS
        ascii-generators.h
        CharacterStats.h
        FontConfigEnumerator.h
        FontEnumerator.h
        FontUtils.h
        init-libs.h
        PangoUtils.h
        )

set (DISPLAY_FONTS_SOURCES
        display-fonts.cpp
        init-libs.cpp
        FontConfigEnumerator.cpp
        FontUtils.cpp
        GlyphRenderer.cpp
        )

set (DISPLAY_FONTS_HEADERS
        init-libs.h
        FontUtils.h
        GlyphRenderer.h
        )

find_package(OpenCV REQUIRED)
find_package(Freetype REQUIRED)
find_package(Pango REQUIRED)
find_package(FontConfig REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${Pango_INCLUDE_DIRS})
include_directories(${FontConfig_INCLUDE_DIRS})

add_executable(ascii-fun ${ASCII_FUN_SOURCES} ${ASCII_FUN_HEADERS})
target_link_libraries(ascii-fun parse_cmd_0_0 ${OpenCV_LIBS})
target_link_libraries(ascii-fun ncurses)
target_link_libraries(ascii-fun ${FREETYPE_LIBRARY})
target_link_libraries(ascii-fun ${Pango_LIBRARY})
target_link_libraries(ascii-fun ${FontConfig_LIBRARY})

add_executable(display-fonts ${DISPLAY_FONTS_SOURCES} ${DISPLAY_FONTS_HEADERS})
target_link_libraries(display-fonts parse_cmd_0_0 ${OpenCV_LIBS})
target_link_libraries(display-fonts ${FREETYPE_LIBRARY})
target_link_libraries(display-fonts ${Pango_LIBRARY})
target_link_libraries(display-fonts ${FontConfig_LIBRARY})
