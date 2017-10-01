// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Demonstration of C++11 usage in Boost.UI.

#include <boost/ui.hpp>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg{"Boost.UI C++11 Demo"};

    ui::listbox listbox = ui::listbox(dlg, {"first", "second", "third"} )
        .on_activate_event([&listbox](ui::index_event& e)
        {
            ui::log::info().spaces() << "Item activated"
                << e.index() << listbox[e.index()];
        })
        ;

    listbox.push_back({U'G', U' ', U'\U0001D11E'});

    listbox.push_back( R"*("(\char)")*");
    listbox.push_back(LR"*("(\wchar_t)")*");
    listbox.push_back(uR"*("(\char16_t)")*");
    listbox.push_back(UR"*("(\char32_t)")*");

    auto str = listbox.at(0) + " c" + L" w" + u" u" + U" U";
    listbox.push_back(str);

    ui::log() << 18446744073709551615ull;

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
