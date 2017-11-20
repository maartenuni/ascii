

#ifndef FONT_CONFIG_ENUMERATOR_H
#define FONT_CONFIG_ENUMERATOR_H

#include "FontEnumerator.h"

class FontConfigEnumerator : public FontEnumerator {
    public:
        FontConfigEnumerator()
            :
                FontEnumerator()
        {
        }

        void enumerate();
        
        int match(const std::string& family,
                  int                style_flags,
                  Font&              out
                  );
};


#endif //ifndef HAVE_FONT_CONFIG_ENUMERATOR_H
