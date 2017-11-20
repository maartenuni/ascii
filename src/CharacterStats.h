
#ifndef HAVE_CHARACTER_STATS_H
#define HAVE_CHARACTER_STATS_H

#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

/**
 * CharacterStats a class to determine the relative brightness of a
 * given text input.
 */
class CharacterStats {

    public:

        enum FontWeight {
            FontBold,
            FontNormal
        };

        class WeightedCharacter {
            public:
                std::string c;
                int         font_weight;
        };

        CharacterStats(
                const std::string& input,
                const std::string& font,
                int                pointsize = -1
                );

        std::string getSet(bool reversed=false) const;

    protected:

        void m_compute_weights();

    private:

        std::string m_input;
        std::string m_font;
        int         m_pointsize;
        std::vector<WeightedCharacter> m_weighted_chars;
};

#endif //ifndef HAVE_CHARACTER_STATS_H
