
#include <assert.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <fontconfig/fontconfig.h>

/* *********************** Library data section ************************* */

FT_Library freetype_lib;

/* *********************** init_lib x ************************** */
// these functions should be static and return 0 when successful

static int init_fontconfig()
{
    FcBool is_init;
    is_init = FcInit();
    return is_init == FcTrue ? 0 : 1;
}

static int init_freetype()
{
    int ret;
    ret = FT_Init_FreeType(&freetype_lib);
    if (ret != FT_Err_Ok) {
        fprintf(stderr, "Unable to init freetype.\n");
        ret = 1;
    }
    return ret;
}

/* *********************** free_lib x ************************** */
// these functions return 0 when successful

static int free_fontconfig()
{
    FcFini();
    return 0;
}

static int free_freetype()
{
    FT_Done_FreeType(freetype_lib);
    return 0;
}

/* ********************** public functions *********************** */

int init_libs()
{
    int ret = 0;
    ret = init_fontconfig();
    if (ret) {
        fprintf(stderr, "Unable to initialize fontconfig.\n");
        return ret;
    }
    
    ret = init_freetype();
    if (ret) {
        fprintf(stderr, "Unable to initialize freetype.\n");
        return ret;
    }

    return ret;
}

int free_libs()
{
    int error_occurred = 0;
    int ret = 0;
    ret = free_fontconfig();
    if (ret)
        error_occurred = 1;
    assert(ret == 0);

    ret = free_freetype();
    if (ret)
        error_occurred = 1;
    assert(ret == 0);
    return error_occurred;
}

