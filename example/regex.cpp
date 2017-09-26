// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>
#include <boost/bind.hpp>

#if !defined(BOOST_NO_CXX11_HDR_REGEX)
#include <regex>
namespace regex_ns = std;
#else
#include <boost/regex.hpp>
namespace regex_ns = boost;
#endif

namespace ui = boost::ui;

class regex_dialog : public ui::dialog
{
    typedef regex_dialog this_type;

public:
    regex_dialog();

private:
    void on_match(bool entire);
    void on_replace();

    regex_ns::wregex get_pattern() const;

    ui::textbox m_input;
    ui::textbox m_output;
    ui::stringbox m_pattern;
    ui::stringbox m_format;
    ui::checkbox m_case_sensetive;
};

regex_dialog::regex_dialog() : ui::dialog(
#if !defined(BOOST_NO_CXX11_HDR_REGEX)
    "C++11 "
#else
    "Boost."
#endif
    "Regex + Boost.UI example")
{
    ui::vbox(*this)
        << m_input.create(*this, "Hello, World!")
            .tooltip("Input data")
            .layout().stretch().justify()
        << (ui::hbox().layout().justify()
            << m_pattern.create(*this, "(\\w+)[ ,]+(\\w+)(.*)")
                .tooltip("Regex pattern")
                .layout().stretch()
            << m_case_sensetive.create(*this, "&Case sensetive")
                .check()
           )
        << (ui::hbox().layout().justify()
            << ui::button(*this, "&Search")
                .on_press(boost::bind(&this_type::on_match, this, false))
                .tooltip("Searches any part of a sequence")
            << ui::button(*this, "&Match")
                .on_press(boost::bind(&this_type::on_match, this, true))
                .tooltip("Searches an entire sequence")
            << ui::button(*this, "&Replace")
                .on_press(&this_type::on_replace, this)
                .tooltip("Replaces occurrences with formatted text")
           )
        << (ui::hbox().layout().justify()
            << ui::label(*this, "Format:").layout().margin(1, 0, 1, 1)
            << m_format.create(*this, "[$&]")
                .layout().stretch()
           )
        << m_output.create(*this).tooltip("Output data")
            .layout().stretch(2).justify()
        ;

    resize(400, 400);
}

void regex_dialog::on_match(bool entire)
{
    const std::wstring input = m_input.text().wstring();
    const regex_ns::wregex pattern = get_pattern();

    m_output.clear();
    regex_ns::wsmatch results;

    if ( entire )
    {
        if ( !regex_ns::regex_match(input, results, pattern) )
            return;
    }
    else
    {
        if ( !regex_ns::regex_search(input, results, pattern) )
            return;
    }

    std::wostringstream ss;
    ss << L"prefix: \"" << results.prefix() << "\" ( $` )\n";
    ss << L"suffix: \"" << results.suffix() << "\" ( $' )\n";
    for ( regex_ns::wsmatch::const_iterator iter = results.begin();
            iter != results.end(); ++iter )
    {
        const regex_ns::wssub_match sub_match = *iter;
        const regex_ns::wsmatch::difference_type i =
            std::distance(results.begin(), iter);
        ss << L'$' << i << L": \"" << sub_match << L'"';
        if ( i == 0 )
            ss << L" ( $& )";
        ss << std::endl;
    }
    ss << L"format: \"" << results.format(m_format.text().wstring()) << "\"";
    m_output.text(ss.str());
}

void regex_dialog::on_replace()
{
    const std::wstring input = m_input.text().wstring();
    const regex_ns::wregex pattern = get_pattern();
    m_output.text(regex_ns::regex_replace(
        input, pattern, m_format.text().wstring() ));
}

regex_ns::wregex regex_dialog::get_pattern() const
{
    regex_ns::wregex re = regex_ns::wregex(m_pattern.text().wstring(),
                                           m_case_sensetive.is_checked()
        ? regex_ns::regex_constants::ECMAScript
        : regex_ns::regex_constants::ECMAScript|regex_ns::regex_constants::icase);

    //re.imbue(ui::getloc());

    return re;
}

int ui_main()
{
    regex_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
