
#ifndef PANGO_UTILS_H
#define PANGO_UTILS_H

#include "FontEnumerator.h"

class PangoFontEnumerator : public FontEnumerator {

    protected:

        void enumerate()
        {
        }

    public:

        PangoFontEnumerator();
        
        bool fontExists(const std::string& font_fam_name) const;

};

#endif // ifndef PANGO_UTILS_H
