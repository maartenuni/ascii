
#include <memory>
#include <string>
#include <cstring>
#include "FontConfigEnumerator.h"
#include <fontconfig/fontconfig.h>

using std::shared_ptr;
using std::string;

void FontConfigEnumerator::enumerate()
{
    shared_ptr<FcPattern>   pattern;
    shared_ptr<FcObjectSet> objset;
    shared_ptr<FcFontSet>   fontset;

    pattern = shared_ptr<FcPattern>(FcPatternCreate(), FcPatternDestroy);
    objset  = shared_ptr<FcObjectSet>(FcObjectSetCreate(), FcObjectSetDestroy);
    if (!pattern || !objset)
        return;

    FcObjectSetAdd(objset.get(), FC_FAMILY);
    FcObjectSetAdd(objset.get(), FC_STYLE);
    FcObjectSetAdd(objset.get(), FC_FILE);

    fontset = shared_ptr<FcFontSet>(
            FcFontList(NULL, pattern.get(), objset.get()),
            FcFontSetDestroy
            );
    FcFontSet *set = fontset.get();
    fprintf(stdout, "found %d fonts\n", set->nfont);
    for (auto i = 0u; i < set->nfont; i++) {
        FcResult r1, r2;
        unsigned char* ffn = NULL;
        unsigned char* ffam = NULL;

        r1 = FcPatternGetString(
                set->fonts[i], FC_FILE, 0, &ffn
                );
        r2 = FcPatternGetString(
                set->fonts[i], FC_FAMILY, 0, &ffam
                );

        if (r1 == FcResultMatch && r2 == FcResultMatch) {
            string file(&ffn[0], &ffn[0] + strlen((char*)ffn));
            string fam(&ffam[0], &ffam[0] + strlen((char*)ffam));
            list({fam, file});
        } else {
            fprintf(stdout, "Oops no match\n");
        }
    }
}

int
FontConfigEnumerator::match(const std::string& family,
                            int style_flags,
                            Font& out
                            )
{
    shared_ptr<FcPattern>   input, output;
    unsigned char*          famname = NULL;
    unsigned char*          fontfn = NULL;
    FcResult                result;

    input = std::shared_ptr<FcPattern>(FcPatternCreate(), FcPatternDestroy);
    if (!input)
        return -1;

    FcPatternAddString(input.get(),
                       FC_FAMILY,
                       (unsigned char*)family.c_str()
                       );

    if (style_flags & BOLD)
        FcPatternAddString(input.get(), FC_STYLE, (unsigned char*)"bold");
    if (style_flags & ITALIC)
        FcPatternAddString(input.get(), FC_STYLE, (unsigned char*)"italic");
    if (style_flags & OBLIQUE)
        FcPatternAddString(input.get(), FC_STYLE, (unsigned char*)"oblique");
    if (style_flags & BOOK)
        FcPatternAddString(input.get(), FC_STYLE, (unsigned char*)"book");

    FcDefaultSubstitute(input.get());
    if (FcConfigSubstitute(NULL, input.get(), FcMatchPattern) != FcTrue)
        return -2;

    output = std::shared_ptr<FcPattern>(
            FcFontMatch(NULL, input.get(), &result),
            FcPatternDestroy
            );
    if (result == FcResultOutOfMemory)
        return -6;
    
    FcResult match = FcPatternGetString(output.get(), FC_FAMILY, 0, &famname);
    if(match != FcResultMatch)
        return -3;
    match = FcPatternGetString(output.get(), FC_FILE, 0, &fontfn);
    if(match != FcResultMatch)
        return -4;


    out.familyname =
        std::string(&famname[0], &famname[0] + strlen((char*) famname));
    out.filename   =
        std::string(&fontfn[0], &fontfn[0] + strlen((char*) fontfn));

    return 0;    
}


