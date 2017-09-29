// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Text processor
// This example creates dialog with input and output fields, and one button
// between them. When user press button, input field text copied into output field.
// Input field is cleared.

#include <boost/ui.hpp>
#include <sstream>

namespace ui = boost::ui;

class bootstrap_dialog : public ui::dialog
{
    typedef bootstrap_dialog this_type;

public:
    bootstrap_dialog();

private:
    void process();

    ui::textbox m_input_widget;
    ui::label m_output_widget;
};

bootstrap_dialog::bootstrap_dialog()
    : ui::dialog("Bootstrap example")
{
    ui::vbox(*this)
        << m_input_widget.create(*this, "Input data")
            .tooltip("Input string")
            .layout().justify().stretch()
        << ui::button(*this, "&Process")
            .on_press(&this_type::process, this)
        << m_output_widget.create(*this)
            .tooltip("Output")
            .layout().justify().stretch()
        ;

    resize(500, 400);
}

void bootstrap_dialog::process()
{
    std::wostringstream ss;

    // TODO: Add your process code here
    ss << m_input_widget.text();

    m_output_widget.text(ss.str());
    m_input_widget.clear();
}

int ui_main()
{
    bootstrap_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
