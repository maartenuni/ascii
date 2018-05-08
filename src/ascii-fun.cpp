
#include <parse_cmd_0/parse_cmd.h>
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include <memory>
#include <cassert>

#include "ascii-generators.h"
#include "init-libs.h"
#include "FontConfigEnumerator.h"
#include "FontEnumerator.h"

using std::string;
using std::shared_ptr;
using std::make_shared;

cmd_option predef_options[] = {
    {'h', "help",           OPT_FLAG,   {}},
    {'d', "display",        OPT_FLAG,   {}},
    {'s', "smooth",         OPT_INT,    {}},
    { 0 , "smooth-method",  OPT_STR,    {}},
    {'r', "reverse",        OPT_FLAG,   {}},
    {'l', "list-fonts",     OPT_FLAG,   {}},
    { 0 , "sobel",          OPT_INT,    {}},
    {'c', "canny",          OPT_INT,    {}},
    {'f', "font",           OPT_STR,    {}},
    { 0 , "font-file",      OPT_STR,    {}},
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

    if (option_context_have_option(context, "list-fonts")) {
        *stop = 1;
        FontConfigEnumerator enumerator;
        enumerator.enumerate();
        auto it = enumerator.beginByFile();
        for(int i= 1; it != enumerator.endByFile(); it++, i++) {
            fprintf(stdout, "%d:%s:%s\n",
                    i,
                    it->second.familyname.c_str(),
                    it->second.filename.c_str()
                    );
        }
        return 0;
    }
    
    if (option_context_nargs(context) == 0) {
        fprintf(stderr, "%s needs at least 1 argument\n", argv[0]);
        option_context_free(context);
        *out = NULL;
        return 1;
    }

    return ret;
}

int generateAscii(option_context* opts, int rows, int cols) {
    for (auto i = 0; i < option_context_nargs(opts); ++i) {
        string fn = option_context_get_argument(opts, i);
        if (1)
            generate_default(opts, fn, rows, cols);
    }

    return 0;
}

int main(int argc, char** argv) {

    int ret, stop = 0;
    int rows, cols;
    option_context *context = NULL;

    ret = init_libs();
    if (ret) {
        fprintf(stderr, "Unable to initialize libraries.\n");
        return -1;
    }

    ret = parse_options(argc, argv, &context, &stop);

    if (!ret && !stop) {
        initscr();
        getmaxyx(stdscr, rows, cols);
        endwin();

        generateAscii(context, rows, cols);
    }

    option_context_free(context);

    free_libs();

    return 0;
}

