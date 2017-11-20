
#ifndef INIT_LIBS_H
#define INIT_LIBS_H

#include<ft2build.h>
#include FT_FREETYPE_H

int init_libs();
int free_libs();

extern FT_Library freetype_lib;

#endif //ifndef INIT_LIBS_H
