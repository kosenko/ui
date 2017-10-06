// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Parse user data using Boost.Spirit.
// Not finished yet.

#include <boost/ui.hpp>
#include <boost/bind.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_utree.hpp>

#include <iterator>

namespace ui = boost::ui;

template <class Iterator>
struct calculator : boost::spirit::qi::grammar<Iterator,
    boost::spirit::ascii::space_type, boost::spirit::utree()>
{
    calculator() : calculator::base_type(expression)
    {
        using boost::spirit::qi::char_;

        expression =
            term
            >> *(   (char_('+') >> term)
                |   (char_('-') >> term)
                )
            ;

        term =
            factor
            >> *(   (char_('*') >> factor)
                |   (char_('/') >> factor)
                )
            ;

        factor =
            boost::spirit::qi::double_
            |   '(' >> expression >> ')'
            |   (char_('-') >> factor)
            |   (char_('+') >> factor)
            ;

        BOOST_SPIRIT_DEBUG_NODE(expression);
        BOOST_SPIRIT_DEBUG_NODE(term);
        BOOST_SPIRIT_DEBUG_NODE(factor);
    }

    boost::spirit::qi::rule<Iterator, boost::spirit::ascii::space_type, boost::spirit::utree()> expression;
    boost::spirit::qi::rule<Iterator, boost::spirit::ascii::space_type, boost::spirit::utree::list_type()> term;
    boost::spirit::qi::rule<Iterator, boost::spirit::ascii::space_type, boost::spirit::utree::list_type()> factor;
};

template <class Iterator>
void phrase_parse(Iterator first, Iterator last)
{
    calculator<Iterator> calc;
    boost::spirit::utree ut;
    Iterator begin = first;
    const bool result = boost::spirit::qi::phrase_parse(
        first, last, calc, boost::spirit::ascii::space, ut);

    if ( !result || first != last )
    {
        std::ostringstream ss;
        ss  << "Parser error at position " << (first - begin)
            << ", text: \""
            << std::basic_string< typename std::iterator_traits<Iterator>::value_type >(first, last)
            << "\"";
        BOOST_THROW_EXCEPTION( std::runtime_error(ss.str()) );
    }

    ui::log() << "Parsed: " << ut;
}

class spirit_dialog : public ui::dialog
{
    typedef spirit_dialog this_type;

public:
    spirit_dialog();

private:
    void on_parse();

    ui::string_box m_input_widget;
};

spirit_dialog::spirit_dialog() : ui::dialog("Boost.Spirit + Boost.UI example")
{
    ui::hbox(*this)
        << m_input_widget.create(*this, "(11.1 + 2 * 3 - 1) / 2")
            .layout().stretch()
        << ui::button(*this, "&Parse")
            .on_press(&this_type::on_parse, this)
        ;
}

void spirit_dialog::on_parse()
{
    const std::string input = m_input_widget.text().string();
    phrase_parse(input.begin(), input.end());
}

int ui_main()
{
    spirit_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
