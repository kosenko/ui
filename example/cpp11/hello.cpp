// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// "Hello, World" example
// This example creates dialog with one button. When user press button
// informational dialog is shown.

// Include all Boost.UI headers
#include <boost/ui.hpp>

namespace ui = boost::ui;

int ui_main()
{
    // Create dialog window with title
    ui::dialog dlg("Hello, Boost.UI!");

    // Put button with title on this dialog window
    ui::button(dlg, "Say &hello")
        // Subscribe to button press events to callback function
        .on_press([]
        {
            // Handle button press event

            // Show informational dialog window with text
            // and wait while user close it
            ui::info_dialog("Hello, C++ World!");
        });

    // Show dialog window
    // and wait while user close it
    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    // Initialize GUI, call ui_main function, uninitialize GUI, catch exceptions
    return ui::entry(&ui_main, argc, argv);
}
