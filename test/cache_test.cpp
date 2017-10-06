// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

namespace ui = boost::ui;

void test_label(ui::dialog& dlg)
{
    ui::label l1;
    BOOST_TEST(!l1.native_valid());
    BOOST_TEST_EQ(l1.text(), "");
    BOOST_TEST_EQ(l1.pos(), ui::point());
    BOOST_TEST_EQ(l1.dimensions(), ui::size());
    BOOST_TEST(l1.is_enabled());
    BOOST_TEST(l1.is_shown()); // TODO: false

    //boost::function<void()> f1;
    //l1.on_mouse_move(f1);

    l1  .create("test label")
        .move(5, 5)
        .resize(200, 100)
        .disable()
        .hide()
        ;
    BOOST_TEST(!l1.native_valid());
    BOOST_TEST_EQ(l1.text(), "test label");
    BOOST_TEST_EQ(l1.pos(), ui::point(5, 5));
    BOOST_TEST_EQ(l1.dimensions(), ui::size(200, 100));
    BOOST_TEST(!l1.is_enabled());
    BOOST_TEST(!l1.is_shown());

    const ui::label l2 = l1;
    BOOST_TEST(!l1.native_valid());
    BOOST_TEST(!l2.native_valid());

    dlg << l1;
    BOOST_TEST(l1.native_valid());
    BOOST_TEST(l2.native_valid());
    BOOST_TEST_EQ(l1.text(), "test label");
    BOOST_TEST_EQ(l2.text(), "test label");
    BOOST_TEST_EQ(l1.pos(), ui::point(5, 5));
    BOOST_TEST_EQ(l2.pos(), ui::point(5, 5));
    BOOST_TEST_EQ(l1.dimensions(), ui::size(200, 100));
    BOOST_TEST_EQ(l2.dimensions(), ui::size(200, 100));
    BOOST_TEST(!l1.is_enabled());
    BOOST_TEST(!l2.is_enabled());
    BOOST_TEST(!l1.is_shown());
    BOOST_TEST(!l2.is_shown());

    dlg.show();
    BOOST_TEST(!l1.is_shown());
    BOOST_TEST(!l2.is_shown());

    l1  .text("new")
        .move(10, 15)
        .resize(300, 150)
        .enable()
        .show()
        ;
    BOOST_TEST(l1.native_valid());
    BOOST_TEST(l2.native_valid());
    BOOST_TEST_EQ(l1.text(), "new");
    BOOST_TEST_EQ(l2.text(), "new");
    BOOST_TEST_EQ(l1.pos(), ui::point(10, 15));
    BOOST_TEST_EQ(l2.pos(), ui::point(10, 15));
    BOOST_TEST_EQ(l1.dimensions(), ui::size(300, 150));
    BOOST_TEST_EQ(l2.dimensions(), ui::size(300, 150));
    BOOST_TEST(l1.is_enabled());
    BOOST_TEST(l2.is_enabled());
    BOOST_TEST(l1.is_shown());
    BOOST_TEST(l2.is_shown());

    boost::function<void()> f2;
    l1.on_mouse_move(f2);
}

int ui_main()
{
    ui::dialog dlg("Cache Test");

    test_label(dlg);

    //dlg.show_modal();

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
