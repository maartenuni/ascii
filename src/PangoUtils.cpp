
#include "PangoUtils.h"
#include <pango/pango.h>
#include <cassert>

PangoFontEnumerator::PangoFontEnumerator()
{
    //PangoFontDescription   *description = NULL;
    PangoContext           *context     = NULL;
    PangoFontMap           *fmap        = NULL;

    //description = pango_font_description_new();
    //context = pango_context_new();

    // perhaps better to try cairo...
    //fmap = pango_ft2_font_map_new(NULL);
    assert(fmap);

    //if (!description)
        return;
}

bool PangoFontEnumerator::fontExists(const std::string& font_fam_name) const
{
    assert(0 == 1);// implement
    return false;
}
