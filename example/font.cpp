// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Show font styles available in Boost.UI.

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <sstream>

#include "to_string.hpp"

namespace ui = boost::ui;

class font_dialog : public ui::dialog
{
    typedef font_dialog this_type;

public:
    font_dialog();

private:
    void set_family();
    void set_font();
    void reset();
    void update_family();

    ui::choice m_family_widget;
    ui::string_box m_name_widget;
    ui::string_box m_size_widget;
    ui::choice m_slant_widget;
    ui::choice m_weight_widget;
    ui::label m_output_widget;

    ui::font m_intial_font;
};

font_dialog::font_dialog()
    : ui::dialog("Boost.UI font example")
{
    static const char* families[] =
    {
        "Serif", "Sans-serif", "Cursive", "Fantasy", "Monospace"
    };
    static const char* slants[] =
    {
        "Normal", "Italic", "Oblique"
    };
    static const char* weights[] =
    {
        "Normal", "Bold"
    };

    ui::vbox(*this)
        << ( ui::hbox().layout().justify()
            << m_family_widget.create(*this, families)
                .on_select(boost::bind(&this_type::set_family, this))
                .tooltip("Font family")
                .layout()
            << m_name_widget.create(*this, font().name())
                .tooltip("Font name")
                .layout().stretch()
            << m_size_widget.create(*this, to_string( font().size_pt() ))
                .tooltip("Font size")
            << m_slant_widget.create(*this, slants)
                .on_select(boost::bind(&this_type::set_font, this))
                .select(0)
                .tooltip("Font slant")
                .layout()
            << m_weight_widget.create(*this, weights)
                .on_select(boost::bind(&this_type::set_font, this))
                .select(0)
                .tooltip("Font weight")
                .layout()
           )
        << ( ui::hbox().layout().justify()
            << ui::button(*this, "&Set font")
                .on_press(&this_type::set_font, this)
            << ui::button(*this, "&Reset")
                .on_press(&this_type::reset, this)
           )
        << m_output_widget.create(*this, "The quick brown fox jumps over the lazy dog")
            .layout().justify().stretch()
        ;

    m_intial_font = m_output_widget.font();

    resize(600, 200);
}

void font_dialog::set_family()
{
    ui::font f = m_output_widget.font();

    ui::font::family family;
    switch ( m_family_widget.current_selection_index() )
    {
        case 0: family = ui::font::family::serif;      break;
        case 1: family = ui::font::family::sans_serif; break;
        case 2: family = ui::font::family::cursive;    break;
        case 3: family = ui::font::family::fantasy;    break;
        case 4: family = ui::font::family::monospace;  break;
        default: return;
    }
    f.set_family(family);

    m_name_widget.text(f.name());
    m_output_widget.font(f);
}

void font_dialog::set_font()
{
    ui::font f = m_output_widget.font();

    f.name( m_name_widget.text() );
    f.size_pt( atof(m_size_widget.text().string().c_str()) );

    ui::font::slant slant;
    switch ( m_slant_widget.current_selection_index() )
    {
        case 0: slant = ui::font::slant::normal;  break;
        case 1: slant = ui::font::slant::italic;  break;
        case 2: slant = ui::font::slant::oblique; break;
        default: return;
    }
    f.set_slant(slant);

    ui::font::weight weight;
    switch ( m_weight_widget.current_selection_index() )
    {
        case 0: weight = ui::font::weight::normal; break;
        case 1: weight = ui::font::weight::bold;   break;
        default: return;
    }
    f.set_weight(weight);

    m_output_widget.font(f);
    update_family();
}

void font_dialog::reset()
{
    m_output_widget.font(m_intial_font);
    m_name_widget.text(m_intial_font.name());
    m_size_widget.text( to_string(m_intial_font.size_pt()) );

    switch ( boost::native_value(m_intial_font.get_slant()) )
    {
        case ui::font::slant::normal:  m_slant_widget.select(0); break;
        case ui::font::slant::italic:  m_slant_widget.select(1); break;
        case ui::font::slant::oblique: m_slant_widget.select(2); break;
    }

    switch ( boost::native_value(m_intial_font.get_weight()) )
    {
        case ui::font::weight::normal: m_weight_widget.select(0); break;
        case ui::font::weight::bold:   m_weight_widget.select(1); break;
    }

    update_family();
}

void font_dialog::update_family()
{
    switch ( boost::native_value(m_output_widget.font().get_family()) )
    {
        case ui::font::family::serif:      m_family_widget.select(0); break;
        case ui::font::family::sans_serif: m_family_widget.select(1); break;
        case ui::font::family::cursive:    m_family_widget.select(2); break;
        case ui::font::family::fantasy:    m_family_widget.select(3); break;
        case ui::font::family::monospace:  m_family_widget.select(4); break;
        case ui::font::family::other:      m_family_widget.select(m_family_widget.npos); break;
    }
}

int ui_main()
{
    font_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
