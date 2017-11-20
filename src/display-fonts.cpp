
#include <parse_cmd_0/parse_cmd.h>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <cassert>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

#include "init-libs.h"
#include "FontConfigEnumerator.h"
#include "GlyphRenderer.h"

using std::string;
using std::shared_ptr;
using std::make_shared;

cmd_option predef_options[] = {
    {'h', "help",           OPT_FLAG,   {}},
    {'f', "font",           OPT_STR,    {}},
    {'f', "font-size",      OPT_INT,    {}},
    {'f', "save-bitmaps",   OPT_FLAG,   {}},
};

int parse_options(int argc, char** argv, option_context** out, int* stop)
{
    int ret, exit;
    option_context *context = NULL;
    ret = options_parse(
            &context,
            argc,
            argv,
            predef_options,
            sizeof(predef_options)/sizeof(predef_options[0])
            );

    *out = context;

    if (ret != OPTION_OK) {
        option_context_free(context);
        *out = NULL;
        return ret;
    }

    return ret;
}

void render_fonts(option_context* context)
{
    int res, fontsize = 80;
    std::string fontfam = "Dejavu Sans Mono";
    std::string charset = "bcgjM.`@$";
    FontConfigEnumerator fontenum;
    FontConfigEnumerator::Font font;
    std::vector<cv::Mat> charbmaps;
    
    if (option_context_have_option(context, "font")) {
        const char* ff = NULL;
        option_context_str_value(context, "font", &ff);
        fontfam = ff;
    }
    
    if (option_context_have_option(context, "font-size")) {
        int fs = 0;
        option_context_int_value(context, "font-size", &fs);
        fontsize = fs;
    }
    
    res = fontenum.match(fontfam, 0, font);
    GlyphRenderer renderchars(font.filename, charset, fontsize);
    renderchars.renderSet(charbmaps);
    
    for (auto i = 0u; i < charset.size() && i < charbmaps.size(); i++) {
        cv::namedWindow(charset.substr(i, 1));
        cv::imshow(charset.substr(i, 1), charbmaps[i]);
        if (option_context_have_option(context, "save-bitmaps"))
            cv::imwrite(charset.substr(i, 1) + ".png", charbmaps[i]);
    }
    cv::waitKey();
}

int main(int argc, char** argv) {

    int ret, stop = 0;
    option_context *context = NULL;

    ret = init_libs();
    if (ret) {
        fprintf(stderr, "Unable to initialize libraries.\n");
        return -1;
    }

    ret = parse_options(argc, argv, &context, &stop);

    if (!ret && !stop) {
        render_fonts(context);
    }

    option_context_free(context);

    free_libs();

    return 0;
}

