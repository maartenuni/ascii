
#ifndef FONT_ENUMERATOR_H
#define FONT_ENUMERATOR_H

#include <string>
#include <map>

class FontEnumerator {

    public:

        struct Font {
            std::string familyname;
            std::string filename;
        };

        enum font_style {
            REGULAR = 0,
            BOLD    = 1 << 0,
            ITALIC  = 1 << 1,
            OBLIQUE = 1 << 2,
            BOOK    = 1 << 3
        };

        typedef std::map<std::string, Font>::const_iterator const_iterator;

        /**
         * Provide a font family name and obtain a font
         *
         */
        int byFamilyName(const std::string& famname, Font& font) const 
        {
            int ret = 0;
            auto it = m_fonts_fam.find(famname);
            if (it == m_fonts_fam.end())
                return -1;
            font = it->second;
            return 0;
        }

        int byFileName(const std::string& filename, Font& font) const
        {
            int ret = 0;
            auto it = m_fonts_file.find(filename);
            if (it == m_fonts_file.end())
                return -1;
            font = it->second;
            return 0;
        }

        virtual int match(const std::string& family,
                          int                style_flags,
                          Font&              out
                          ) = 0;

        virtual void enumerate() = 0;

        const_iterator beginByFamily() const {return m_fonts_fam.cbegin();}
        const_iterator beginByFile() const   {return m_fonts_file.cbegin();}
        const_iterator endByFamily() const   {return m_fonts_fam.cend();}
        const_iterator endByFile() const     {return m_fonts_file.cend();}

    protected:

        void list(Font f)
        {
            m_fonts_file[f.filename] = f;
            m_fonts_fam [f.familyname ] = f;
        }

    private:

        std::map<std::string, Font> m_fonts_file;
        std::map<std::string, Font> m_fonts_fam;
};

#endif //ifndef FONT_ENUMERATOR_H
