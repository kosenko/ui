// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Demonstration of C++11 usage in Boost.UI.

#include <boost/ui.hpp>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg{"Boost.UI C++11 Demo"};

    ui::list_box list_box = ui::list_box(dlg, {"first", "second", "third"} )
        .on_activate_event([&list_box](ui::index_event& e)
        {
            ui::log::info().spaces() << "Item activated"
                << e.index() << list_box[e.index()];
        })
        ;

// Requires at least Visual C++ 14.0 (2015)
#if !defined(_MSC_VER) || (_MSC_VER >= 1900)
    list_box.push_back({U'G', U' ', U'\U0001D11E'});

    list_box.push_back( R"*("(\char)")*");
    list_box.push_back(LR"*("(\wchar_t)")*");
    list_box.push_back(uR"*("(\char16_t)")*");
    list_box.push_back(UR"*("(\char32_t)")*");

    auto str = list_box.at(0) + " c" + L" w" + u" u" + U" U";
    list_box.push_back(str);
#endif

    ui::log() << 18446744073709551615ull;

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
