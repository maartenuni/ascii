
#ifndef GLYPH_RENDERER_H
#define GLYPH_RENDERER_H

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <exception>
#include <ft2build.h>
#include FT_FREETYPE_H

class GlyphRenderer {

    public:

        enum error {
            SUCCES,
            UNKNOWN_FONT_FORMAT,
            UNABLE_TO_OPEN_FONT,
        };

        GlyphRenderer(
                const std::string&  fontfile,
                const std::string&  charset,
                int                 fontpoints,
                int                 dpi=72
                );

        /**
         * Renders the character from charset into cv::Mat representation
         */
        int renderSet(std::vector<cv::Mat>& chars,
                      bool append=false);

    private:

        /**
         * Turn glyph into opencv matrix.
         *
         * \param [in] slot the slot that describes the Glyph.
         * \param [in] size of the square to fit the glyph in.
         */
        cv::Mat glyphToMat(const FT_GlyphSlot slot, cv::Size size);

        std::string m_fontfile;
        std::string m_charset;
        int         m_pointsize;
        int         m_dpi;
};

#endif //ifndef GLYPH_RENDERER_H
