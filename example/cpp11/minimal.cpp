// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Re-implemented wxWidgets minimal sample:
// https://github.com/wxWidgets/wxWidgets/blob/master/samples/minimal/minimal.cpp

#include <boost/ui.hpp>

namespace ui = boost::ui;

class my_frame : public ui::frame
{
public:
    my_frame(const ui::uistring& title);
};

my_frame::my_frame(const ui::uistring& title)
    : ui::frame(title)
{
    menu_bar()
        << ( ui::menu("&File")
            << ui::menu::item("E&xit\tAlt-X")
                .on_press(&my_frame::close, this)
           )
        << ( ui::menu("&Help")
            << ui::menu::item("&About\tF1")
                .on_press([]
                {
                    std::ostringstream ss;
                    ss  << "Welcome to Boost " << BOOST_VERSION / 100000
                        << '.' << BOOST_VERSION / 100 % 1000
                        << '.' << BOOST_VERSION % 100
                        << "!\n"
                        << "\n"
                        << "This is the minimal Boost.UI sample\n"
                        << "running under " << BOOST_PLATFORM << "."
                        ;
                    ui::info_dialog(ss.str(), "About Boost.UI minimal sample");
                })
           )
        ;
}

int ui_main()
{
    my_frame frame("Minimal Boost.UI App");

    frame.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
