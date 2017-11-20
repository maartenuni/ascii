
#include "CharacterStats.h"
#include "FontConfigEnumerator.h"
#include "init-libs.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <opencv2/core/core.hpp>

#include <iostream>
#include <algorithm>

using namespace std;

CharacterStats::CharacterStats(
        const string& input,
        const string& font,
        int           pointsize
        )
    :
        m_input(input),
        m_font(font),
        m_pointsize(pointsize)
{
    m_compute_weights();
}

static int sum_bitmap(FT_Bitmap* map)
{
    int sum = 0;
    for (auto i = 0u; i < map->width; i++)
    {
        for ( auto j = 0u; j < map->rows; j++)
        {
            sum += map->buffer[j * map->width + i];
        }
    }
    return sum;
}

void CharacterStats::m_compute_weights()
{
    int ret;
    FontEnumerator::Font font;
    FontConfigEnumerator e;

    FT_Library      ftlib = freetype_lib;
    FT_Face         ftface;
    FT_Error        error;
    FT_GlyphSlot    slot;
    
    e.enumerate();
    ret = e.byFamilyName(m_font, font);
    assert(ret == 0);

    const char* fontfn = font.filename.c_str();
    
    error = FT_New_Face(ftlib, fontfn, 0, &ftface);
    if(error == FT_Err_Unknown_File_Format) {
        fprintf(stderr, "The font \"%s\" is in a unknown format.\n",
                m_font.c_str()
                );
        return;
    }
    else if (error) {
        fprintf(stderr, "The font \"%s\" problem with the file.\n",
                fontfn
                );
        return;
    }

    /*TODO Check whether we need to select a char map.*/

    FT_Set_Char_Size(ftface, 0, m_pointsize*64, 0, 0);
    //FT_
    slot = ftface->glyph;

    for (auto i = 0u; i < m_input.size(); i++) {
        int sum;
        error = FT_Load_Char(ftface, m_input[i], FT_LOAD_RENDER);
        if (error)
            continue;

        sum = sum_bitmap(&slot->bitmap);
        m_weighted_chars.push_back({m_input.substr(i, 1), sum});
    }
    auto less_char = [](
            const WeightedCharacter& c1,
            const WeightedCharacter& c2
            )
    {
        return c1.font_weight < c2.font_weight;
    };

    std::sort(m_weighted_chars.begin(), m_weighted_chars.end(), less_char);
}

std::string CharacterStats::getSet(bool reversed) const
{
    std::string output;
    for (const auto& wc : m_weighted_chars) {
        output += wc.c;
    }
    if (!reversed)
        return output;
    else
        return string(output.crbegin(), output.crend());

}

