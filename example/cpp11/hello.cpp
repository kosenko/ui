// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg("Hello, Boost.UI!");

    ui::button(dlg, "Say &hello")
        .on_press([]
        {
            ui::info_dlg("Hello, C++ World!");
        });

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
