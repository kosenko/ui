// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Text processor
// This example creates dialog with input and output fields, and one button
// between them. When user press button, reversed input field text copied into output field.
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

    ui::text_box m_input_widget;
    ui::label m_output_widget;
};

bootstrap_dialog::bootstrap_dialog()
    : ui::dialog("Bootstrap example")
{
    // Create vertical box layout inside dialog window
    // and put children widgets inside it
    ui::vbox(*this)
        << ui::label(*this, "Input:")
        << m_input_widget.create(*this, "Boost.UI default input data 0123456789")
            .tooltip("Input string")
            .layout().justify().stretch()

        << ui::button(*this, "&Process")
            .on_press(&this_type::process, this)
            .tooltip("Process input data")

        << ui::label(*this, "Output:")
        << m_output_widget.create(*this)
            .tooltip("Output")
            .layout().justify().stretch()
        ;

    // Change dialog window size
    resize(400, 300);
}

void bootstrap_dialog::process()
{
    // Read string from input widget
    std::wstring data = m_input_widget.text().wstring();

    // TODO: Add your process code here
    std::reverse(data.begin(), data.end());

    std::wostringstream ss;
    ss << data;

    // Write string to output widget
    m_output_widget.text(ss.str());

    // Clear input widget text
    m_input_widget.clear();
}

int ui_main()
{
    bootstrap_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
