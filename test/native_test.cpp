// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>
#include <boost/ui/native/all.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

#include <wx/wx.h>

namespace ui = boost::ui;

void test_label(ui::widget& parent)
{
    {
        ui::label l;
        l.create(parent, "text");
        BOOST_TEST_EQ(ui::native::from_widget(l)->GetWindowStyleFlag(), 0);
        ui::native::modify_style_flags(l, wxALIGN_RIGHT);
        BOOST_TEST_EQ(ui::native::from_widget(l)->GetWindowStyleFlag(), wxALIGN_RIGHT);
    }
    {
        ui::label l;
        ui::native::modify_style_flags(l, wxALIGN_RIGHT);
        l.create(parent, "text");
        BOOST_TEST_EQ(ui::native::from_widget(l)->GetWindowStyleFlag(), wxALIGN_RIGHT);
    }
}

int ui_main()
{
    ui::dialog dlg("Title");

    test_label(dlg);

    //dlg.show_modal();

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
