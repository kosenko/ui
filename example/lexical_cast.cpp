// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Show boost::lexical_cast<> work using user provided data.

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string/split.hpp> // boost::split()
#include <boost/algorithm/string/classification.hpp> // boost::is_any_of()

#include <boost/lexical_cast.hpp>

namespace ui = boost::ui;

class lc_dialog : public ui::dialog
{
    typedef lc_dialog this_type;

public:
    lc_dialog();

private:
    void convert();

    ui::textbox m_input_widget;
    ui::label m_output_widget;
    ui::choice m_type_choice;
};

lc_dialog::lc_dialog() : ui::dialog("Boost.Lexical_Cast + Boost.UI example")
{
    static const char* types[] = { "short", "unsigned short", "int", "float",
        "bool", "wchar_t", "std::wstring" };

    ui::vbox(*this)
        << ( ui::hbox()
            << ui::label(*this, "Convert to: ")
                .layout().stretch()
            << m_type_choice.create(*this, types)
                .on_select(boost::bind(&this_type::convert, this))
                .select(0)
                .layout().stretch()
           ).layout().justify()
        << ( ui::hbox()
            << m_input_widget.create(*this, "0\n1\n123\n-4\n5.6\n5,6\n1000000\n1e6\ninf\nx\ntext")
                .on_edit(boost::bind(&this_type::convert, this))
                .tooltip("Input")
                .layout().justify().stretch()
            << m_output_widget.create(*this)
                .tooltip("Output")
                .layout().justify().stretch()
           ).layout().justify().stretch()
                ;

    convert();
}

template <class T>
static std::wstring convert_to(const std::vector<std::wstring>& input_strings)
{
    std::wostringstream ss;

    for ( std::vector<std::wstring>::const_iterator iter = input_strings.begin();
         iter != input_strings.end(); ++iter )
    {
        try
        {
            ss << boost::lexical_cast<T>(*iter);
        }
        catch (const boost::bad_lexical_cast&)
        {
            ss << L"(Bad lexical cast)";
        }
        ss << std::endl;
    }

    return ss.str();
}

void lc_dialog::convert()
{
    const std::wstring input = m_input_widget.text().wstring();

    std::vector<std::wstring> input_strings;
    boost::split(input_strings, input, boost::is_any_of(L"\n"));

    std::wstring output;
    switch ( m_type_choice.current_selection_index() )
    {
        case 0: output = convert_to<short>(input_strings); break;
        case 1: output = convert_to<unsigned short>(input_strings); break;
        case 2: output = convert_to<int>(input_strings); break;
        case 3: output = convert_to<float>(input_strings); break;
        case 4: output = convert_to<bool>(input_strings); break;
        case 5: output = convert_to<wchar_t>(input_strings); break;
        case 6: output = convert_to<std::wstring>(input_strings); break;
    }
    m_output_widget.text(output);
}

int ui_main()
{
    lc_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
