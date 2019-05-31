
#include <string>
#include <iostream>
#include <parse_cmd_0_0/parse_cmd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "CharacterStats.h"

using std::string;
using std::cout;
using std::endl;

const string CHARS = " .,-:^;=+*%[ea{A$bdWBM";
//const string CHARS = " .-:^=+[a{A$WM";
//const string CHARS = "`~1234567890-=\\!@#$%^&*()_+|"
//                     "QWERTYUIOP[]qwertyuiop{}"
//                     "ASDFGHJKL;'asdfghjkl:\""
//                     "ZXCVBNM,./zxcvbnm<>?";

const string INPUT = "input";
const string OUTPUT= "output";

int generate_default(
        const option_context* options,
        const string& fn,
        int rows,
        int cols
        )
{
    int smooth = 0;
    bool display = option_context_have_option(options, "display");
    string char_set = CHARS;
    if (display) {
        cv::namedWindow(
                INPUT,
                CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED
                );
        cv::namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE | CV_GUI_EXPANDED);
    }

    CharacterStats cstats(CHARS, "DejaVu Sans Mono", 12);

    char_set = cstats.getSet(
            option_context_have_option(options, "reverse") ? true : false
            );

    cv::Mat input = cv::imread(fn, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat reduced;
    cv::resize(input, reduced, {0,0}, .5, .5);

    if (option_context_have_option(options, "smooth"))
        option_context_int_value(options, "smooth", &smooth);

    if (smooth > 0) {
        string sm;
        const char* sp = NULL;
        if (option_context_have_option(options, "smooth-method")) {
            option_context_str_value(options, "smooth-method", &sp);
            sm = sp;
        }
        if (sm == "median") {
            cv::medianBlur(reduced, reduced, smooth);
        }
        else {
            cv::GaussianBlur(reduced, reduced,
                    cv::Size(smooth, smooth), sqrt(smooth)
                    );
        }
    }

    cv::Size aoi_size(reduced.cols / cols, reduced.rows / rows);
    unsigned wsteps, hsteps;
    for (double r = 0; r < rows; r++) {
        for (double c = 0; c < cols; c++) {
            cv::Point p(c * float(reduced.cols) / cols,
                        r * float(reduced.rows) / rows);
            cv::Rect roi(p, aoi_size);
            cv::Mat tile(reduced, roi);
            cv::Scalar m = cv::mean(tile);
            int index = m[0] / 256.0  * CHARS.size();
            assert(index < char_set.size());
            cout << char_set[index];
        }
        cout << endl;
    }

//    cv::Sobel(reduced, reduced, reduced.depth(), 1, 1, 7, 1);
//
//    cv::erode(reduced, reduced, 
    if (display) {
        imshow(INPUT, input);
        imshow(OUTPUT, reduced);
        cv::waitKey(0);
    }
    return 0;
}
