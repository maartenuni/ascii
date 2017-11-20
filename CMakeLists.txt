
cmake_minimum_required(VERSION 3.1)
project(ascii-fun C CXX)

set (CMAKE_CXX_STANDARD 11)

include (CheckIncludeFiles)
include (CheckIncludeFileCXX)

CHECK_INCLUDE_FILES(parse_cmd_0/parse_cmd.h HAVE_PARSE_CMD_H)
CHECK_INCLUDE_FILE_CXX(cstdlib HAVE_CSTDLIB_H)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

add_subdirectory(src)

