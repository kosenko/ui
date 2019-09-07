// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Show stacktrace in event handler.

#include <boost/ui.hpp>
#include <boost/stacktrace.hpp>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg("Boost.Stacktrace + Boost.UI example");

    ui::button(dlg, "Show &stacktrace")
        .on_press([]
        {
            std::ostringstream info;
            info << boost::stacktrace::stacktrace();
            ui::info_dialog(info.str());
        });

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
