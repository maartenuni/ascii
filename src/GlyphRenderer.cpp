

#include "GlyphRenderer.h"
#include "init-libs.h"
#include "FontUtils.h"
#include FT_GLYPH_H
#include FT_IMAGE_H
#include FT_OUTLINE_H
#include FT_BBOX_H

using std::string;
using std::vector;
using std::pair;
using cv::Mat;

GlyphRenderer::GlyphRenderer(
        const string& fn,
        const string& set,
        int points,
        int dpi
        )
    :
        m_fontfile(fn),
        m_charset(set),
        m_pointsize(points),
        m_dpi(dpi)
{
}

Mat outline_to_mat(const FT_Outline* outline, int descender, cv::Size size)
{
    int error;
    Mat m = Mat::zeros(size, CV_8UC1);

    FT_BBox box;
    FT_Vector pen;
    FT_Outline* copy = (FT_Outline*) calloc(1, sizeof(FT_Outline));
    
    FT_Outline_New(
            freetype_lib,
            outline->n_points,
            outline->n_contours,
            copy
            );
    error = FT_Outline_Copy(outline, copy);
    assert(error == 0);
    error = FT_Outline_Get_BBox(copy, &box);
    assert(error == 0);

    FT_Outline_Translate(
            copy,
           0, //-round_font_unit(box.xMin),
           -ceil_font_unit(box.yMin)
           );

    FT_Bitmap target = {
        static_cast<unsigned>(m.rows),
        static_cast<unsigned>(m.cols),
        static_cast<int>(m.step),
        m.data,
        256,
        FT_PIXEL_MODE_GRAY,
    };
    
    FT_Outline_Get_Bitmap(freetype_lib, copy, &target);
    FT_Outline_Done(freetype_lib, copy);
    free(copy);

    return m;
}

Mat GlyphRenderer::glyphToMat(FT_GlyphSlot slot, cv::Size size)
{
    Mat m(size, CV_8UC1);
    m = cv::Scalar();
    FT_Bitmap* bm = &slot->bitmap;
    
    //FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

    unsigned bm_width = bm->width;
    unsigned bm_height= bm->rows;
    unsigned startCol = slot->bitmap_left;
    unsigned startRow = 0;
    unsigned ascent = slot->face->ascender / 64;

    for (int r = startRow, bmrow = 0; bmrow < bm_height ; r++, bmrow++) {
        if (r >= size.height ||  r < 0)
            continue;
        uint8_t* row = m.data + m.step * r;
        uint8_t* brow= bm->buffer + bmrow * bm->pitch;

        // this lines the characters nicely in the middle on the horizontal
        // axis.
        for (int c = startCol; c < startCol + bm_width; c++) {
            if (c >= size.width || c < 0)
                continue;
            row[c] = brow[(c - startCol)];
        }
    }

    return m;
}

int GlyphRenderer::renderSet(vector<Mat>& output, bool append)
{
    int ret, width, height;
    
    FT_Library      ftlib = freetype_lib;
    FT_Face         ftface;
    FT_Error        error;
    FT_GlyphSlot    slot;
    FT_BBox         bbox;

    if (!append)
        output.clear();
    
    error = FT_New_Face(ftlib, m_fontfile.c_str(), 0, &ftface);
    if(error == FT_Err_Unknown_File_Format) {
        fprintf(stderr, "The font \"%s\" is in a unknown format.\n",
                m_fontfile.c_str()
                );
        return UNKNOWN_FONT_FORMAT;
    }
    else if (error) {
        fprintf(stderr, "The font \"%s\" problem with the file.\n",
               m_fontfile.c_str() 
                );
        return UNABLE_TO_OPEN_FONT;
    }

    /*TODO Check whether we need to select a char map.*/

    FT_Set_Char_Size(ftface, m_pointsize*64, m_pointsize*64, m_dpi, m_dpi);
    //FT_Set_Pixel_Sizes(ftface, m_pointsize, m_pointsize);
    assert(FT_IS_SCALABLE(ftface));
    slot = ftface->glyph;
    bbox = ftface->bbox;

    // calculate dimensions in font_points.
    //width = bbox.xMax / 64 - bbox.xMin / 64;
    //height= bbox.yMax / 64 - bbox.yMin / 64;
    width = ftface->size->metrics.max_advance / 64;
    height= ftface->size->metrics.height / 64;

    width = (int) round(points_to_pixels(width,  m_dpi));
    height= (int) round(points_to_pixels(height, m_dpi));
    //fprintf(stdout, "Width = %d,height = %d, pointsize = %d, dpi = %d\n", width, height, m_pointsize, m_dpi);

    for (auto i = 0u; i < m_charset.size(); i++) {
        FT_Glyph glyph;
        Mat bitmap;
        int gidx;  // glyph index
        
        gidx = FT_Get_Char_Index(ftface, m_charset[i]);
        error = FT_Load_Glyph(ftface, gidx, FT_LOAD_DEFAULT);
        if (error)
            continue;

//        bitmap = glyphToMat(ftface->glyph,
//                            cv::Size(width, height)
//                            );
        bitmap = outline_to_mat(
                &ftface->glyph->outline,
                ceil_font_unit(ftface->descender),
                cv::Size(width, height)
                );

        output.push_back(bitmap);
    }
    return 0;
}
