// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Process user data using Boost.Tokenizer.

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>

#include <sstream>

namespace ui = boost::ui;

//------------------------------------------------------------------------------

class separator_area
{
    typedef separator_area this_type;

protected:
    void create_base(ui::notebook& notebook, const std::string& title,
        const std::string& default_input_value)
    {
        ui::panel panel(notebook);
        notebook.append_page(panel, title);

        ui::vbox box = ui::vbox(panel);

        box << m_input_widget.create(panel, default_input_value)
                .on_edit(&this_type::parse, this)
                .tooltip("Input string")
                .layout().justify();

        do_create(panel, box);

        box << m_output_widget.create(panel)
                .tooltip("Output")
                .layout().justify().stretch();

        parse();
    }

    virtual void do_create(ui::widget& parent, ui::vbox& box) {}

    //typedef char char_type;
    typedef wchar_t char_type;
    //typedef char16_t char_type;
    //typedef char32_t char_type;
    typedef std::basic_string<char_type> string_type;

    void parse()
    {
        do_parse(m_input_widget.text().basic_string<char_type>());
    }

    virtual void do_parse(const string_type& input) = 0;

    template <class Tokenizer>
    void parse_output(Tokenizer& tokens)
    {
        std::basic_ostringstream<char_type> ss;
        for ( typename Tokenizer::iterator tok_iter = tokens.begin();
            tok_iter != tokens.end(); ++tok_iter)
        {
            ss << '\"' << *tok_iter << '\"' << std::endl;
        }

        m_output_widget.text(ss.str());
    }

private:
    ui::string_box m_input_widget;
    ui::label m_output_widget;
};

//------------------------------------------------------------------------------

class char_separator_area : public separator_area
{
    typedef char_separator_area this_type;

public:
    void create(ui::notebook& notebook)
    {
        create_base(notebook, "&Char separator",
            ";;Hello|world||-foo--bar;yow;baz|");
    }

protected:
    virtual void do_create(ui::widget& parent, ui::vbox& box)
    {
        const boost::function<void()> fn_parse =
            boost::bind(&this_type::parse, this);

        box
            << m_dropped_delims_widget.create(parent, "-;")
                .on_edit(fn_parse)
                .tooltip("Dropped delimiters")
                .layout().justify()
            << m_kept_delims_widget.create(parent, "|")
                .on_edit(fn_parse)
                .tooltip("Kept delimiters")
                .layout().justify()
            << m_empty_tokens_check_box.create(parent, "&Allow empty tokens")
                .on_toggle(fn_parse)
                .layout().justify()
            ;
    }

    virtual void do_parse(const string_type& input)
    {
        typedef boost::tokenizer<boost::char_separator<string_type::value_type>,
            string_type::const_iterator, string_type > tokenizer_type;

        const boost::char_separator<string_type::value_type>
            sep(m_dropped_delims_widget.text().basic_string<char_type>().c_str(),
                m_kept_delims_widget   .text().basic_string<char_type>().c_str(),
                m_empty_tokens_check_box.is_checked() ? boost::keep_empty_tokens
                                                      : boost::drop_empty_tokens
               );
        tokenizer_type tokens(input, sep);

        parse_output(tokens);
    }

private:
    ui::string_box m_dropped_delims_widget;
    ui::string_box m_kept_delims_widget;
    ui::check_box m_empty_tokens_check_box;
};

//------------------------------------------------------------------------------

class escaped_list_separator_area : public separator_area
{
public:
    void create(ui::notebook& notebook)
    {
        create_base(notebook, "&Excaped list separator",
            "Field 1,\"putting quotes around fields, allows commas\",Field 3");
    }

protected:
    virtual void do_parse(const string_type& input)
    {
        typedef boost::tokenizer<boost::escaped_list_separator<string_type::value_type>,
            string_type::const_iterator, string_type > tokenizer_type;

        tokenizer_type tokens(input);

        parse_output(tokens);
    }
};

//------------------------------------------------------------------------------

class tokenizer_dialog : public ui::dialog
{
public:
    tokenizer_dialog();

private:
    char_separator_area m_char_separator_area;
    escaped_list_separator_area m_escaped_list_separator_area;
};


tokenizer_dialog::tokenizer_dialog()
    : ui::dialog("Boost.Tokenizer + Boost.UI example")
{
    ui::notebook notebook(*this);
    m_char_separator_area.create(notebook);
    m_escaped_list_separator_area.create(notebook);

    resize(400, 500);
}

int ui_main()
{
    tokenizer_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
