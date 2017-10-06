// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Convert user text to upper, lower cases, etc
// using Boost.Locale or Boost.Algorithm.

#include <boost/ui.hpp>
#include <boost/locale.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/bind.hpp>

namespace ui = boost::ui;

class locale_dialog : public ui::dialog
{
    typedef locale_dialog this_type;

public:
    locale_dialog();

private:
    std::locale get_locale() const;

    void on_init();
    void on_to_lower();
    void on_to_upper();
    void on_to_title();
    void on_fold_case();
    void on_to_lower_algorithm();
    void on_to_upper_algorithm();

    ui::text_box m_input_widget;
    ui::text_box m_output_widget;
    ui::combo_box m_locale_combo_box;
    ui::combo_box m_charset_combo_box;
};

locale_dialog::locale_dialog()
    : ui::dialog("Boost.Locale + Boost.UI Example")
{
    static const char* locales[] =
    {
        "", "C", "POSIX",
        "de_DE.UTF-8", "de_CH.UTF-8",
        "en_GB.UTF-8", "en_US.UTF-8", "en_AU.UTF-8",
        "fr_FR.UTF-8", "fr_CH.UTF-8",
        "he_IL.UTF-8", "ja_JP.SJIS", "ja_JP.UTF-8",
        "ru_RU.UTF-8", "tr_TR.UTF-8", "uk_UA.UTF-8"
    };
    static const char* charsets[] =
    {
        "Latin1",
        "cp1250", "cp1251", "cp1252", "cp1253", "cp1254", "cp1255", "cp1256", "cp1257",
        "iso88591", "iso885913", "iso885915", "iso88592", "iso88593", "iso88594",
        "iso88595", "iso88596", "iso88597", "iso88598", "iso88599",
        "koi8r", "koi8u", "usascii",
        "windows1250", "windows1251", "windows1252", "windows1253",
        "windows1254", "windows1255", "windows1256", "windows1257"
    };

    ui::hbox(*this)
        << ( ui::vbox().layout().justify().stretch()
            << m_input_widget.create(*this)
                .tooltip("Input")
                .layout().justify().stretch()
            << m_output_widget.create(*this)
                .tooltip("Output")
                .layout().justify().stretch()
           )
        << ( ui::vbox().layout().justify()
            << ui::label(*this, "Locale:")
                .layout().margin(1, 1, 0, 1)
            << m_locale_combo_box.create(*this, locales)
                .on_select(boost::bind(&this_type::on_init, this))
                .layout().justify()
            << ui::label(*this, "Charset:")
                .layout().margin(1, 1, 0, 1)
            << m_charset_combo_box.create(*this, charsets)
                .on_select(boost::bind(&this_type::on_init, this))
                .layout().justify()
            << ui::button(*this, "&Init")
                .on_press(&this_type::on_init, this)
                .layout().justify()
            << ui::label(*this, "Boost.Locale:")
            << ui::button(*this, "To &lower")
                .on_press(&this_type::on_to_lower, this)
                .layout().justify()
            << ui::button(*this, "To &upper")
                .on_press(&this_type::on_to_upper, this)
                .layout().justify()
            << ui::button(*this, "To &title")
                .on_press(&this_type::on_to_title, this)
                .layout().justify()
            << ui::button(*this, "&Fold case")
                .on_press(&this_type::on_fold_case, this)
                .layout().justify()
            << ui::label(*this, "Boost.Algorithm:")
            << ui::button(*this, "To l&ower")
                .on_press(&this_type::on_to_lower_algorithm, this)
                .layout().justify()
            << ui::button(*this, "To u&pper")
                .on_press(&this_type::on_to_upper_algorithm, this)
                .layout().justify()
           )
        ;

    m_locale_combo_box.push_back(ui::getloc().name());

    resize(600, 500);

    on_init();
}

std::locale locale_dialog::get_locale() const
{
    return boost::locale::generator()(m_locale_combo_box.text().u8string());
}

void locale_dialog::on_init()
{
    std::ostringstream ss;
    ss << "Hello, world!";
    // Hello World in Chinese language
    ss << " \xE6\x82\xA8" "\xE5\xA5\xBD" "\xE4\xB8\x96" "\xE7\x95\x8C";
    ss << " \xF0\x9D\x84\x9E"; // Musical G-clef
    ss << " \xF0\xA0\x82\x8A"; // Han Character 'U+2008A'
    ss << " \xF0\x9F\x98\x8A \xF0\x9F\x98\x8E"; // smiles
    ss << " \xC3\xA9 e\xCC\x81"; // e-acute
    ss << " gr\xC3\xBC\xC3\x9F""en";
    ss << " \xE1\xBD\x88\xCE\x94\xCE\xA5\xCE\xA3\xCE\xA3\xCE\x95\xCE\x8E\xCE\xA3";


    ss.imbue(get_locale());
    ss << "\nnumber: "   << boost::locale::as::number   << 103.34;
    ss << ", currency: " << boost::locale::as::currency << 103.34;
    ss << "\ndate: "     << boost::locale::as::date     << std::time(0);
    ss << ", time: "     << boost::locale::as::time     << std::time(0);
    ss << boost::locale::format(", date format is {1,date}, time format is {1,time}") % time(0);
    ss << "\n-12345678901 is " << boost::locale::as::spellout << -12345678901;
    ss << "\n0.1234 is " << boost::locale::as::spellout << 0.1234;

    const std::string charset = m_charset_combo_box.text().u8string();
    if ( !charset.empty() )
    {
        std::ostringstream ext_ascii;
        for ( unsigned ch = 0x80; ch <= 0xFF; ch++ )
            ext_ascii << (char)ch;
        ss << std::endl << boost::locale::conv::to_utf<char>(
            ext_ascii.str(), charset);
    }

    m_input_widget.text(ui::utf8( ss.str() ));
}

void locale_dialog::on_to_lower()
{
    m_output_widget.text(
        boost::locale::to_lower(m_input_widget.text().wstring(),
                                get_locale()) );
}

void locale_dialog::on_to_upper()
{
    m_output_widget.text(
        boost::locale::to_upper(m_input_widget.text().wstring(),
                                get_locale()) );
}

void locale_dialog::on_to_title()
{
    m_output_widget.text(
        boost::locale::to_title(m_input_widget.text().wstring(),
                                get_locale()) );
}

void locale_dialog::on_fold_case()
{
    m_output_widget.text(
        boost::locale::fold_case(m_input_widget.text().wstring(),
                                 get_locale()) );
}

void locale_dialog::on_to_lower_algorithm()
{
    m_output_widget.text(
        boost::to_lower_copy(m_input_widget.text().wstring(),
                             get_locale()) );
}

void locale_dialog::on_to_upper_algorithm()
{
    m_output_widget.text(
        boost::to_upper_copy(m_input_widget.text().wstring(),
                             get_locale()) );
}

int ui_main()
{
    locale_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
