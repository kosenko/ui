// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>
#include <boost/optional/optional_io.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

#include <vector>
#include <list>

#define SIZEOF(array) (sizeof(array)/sizeof(array[0]))

#ifdef __WXWINDOWS__
#error Do not include native headers by default
#endif

namespace ui = boost::ui;

void test_dialog(ui::dialog& dlg)
{
    ui::dialog dlg_not_created;
    BOOST_TEST(dlg_not_created.native_handle() == NULL);
    BOOST_TEST(!dlg_not_created.native_valid());

    BOOST_TEST(dlg.native_handle() != NULL);
    BOOST_TEST(dlg.native_valid());

    BOOST_TEST(!dlg.is_shown());

    ui::window win = dlg;
    BOOST_TEST_EQ(win.title(), "Title");
    win.title(win.title() + " test");
    BOOST_TEST_EQ(win.title(), "Title test");
}

void test_canvas(ui::widget parent)
{
    ui::canvas canvas(parent);
    ui::painter painter = canvas.painter();

    BOOST_TEST(painter.native_handle() != NULL);

    {
        std::vector<double> dashes;
        dashes.push_back(10);
        dashes.push_back(8);
        painter.line_dash(dashes);
        painter.line_dash(dashes.begin(), dashes.end());
    }
    {
        std::list<int> dashes;
        dashes.push_back(10);
        dashes.push_back(8);
        painter.line_dash(dashes);
        painter.line_dash(dashes.begin(), dashes.end());
    }
    {
        const int dashes[] = { 10, 8 };
        painter.line_dash(dashes);
    }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    painter.line_dash({ 10, 8 });
#endif
}

void test_button(ui::widget parent)
{
    {
        ui::button button0;
        BOOST_TEST(button0.native_handle() == NULL);
    }

    {
        ui::button button1(parent, "Button 1");
        BOOST_TEST(!button1.is_shown());

        BOOST_TEST_EQ(button1.x(), 0);
        BOOST_TEST_EQ(button1.y(), 0);

        button1.move(5, 10);
        BOOST_TEST_EQ(button1.x(), 5);
        BOOST_TEST_EQ(button1.y(), 10);

        button1.move(ui::point(15, 20));
        BOOST_TEST(button1.pos() == ui::point(15, 20));

        button1.resize(100, 50);
        BOOST_TEST_EQ(button1.width(), 100);
        BOOST_TEST_EQ(button1.height(), 50);
        BOOST_TEST_EQ(button1.dimensions(), ui::size(100, 50));
        BOOST_TEST_EQ(button1.bounds(), ui::rect(15, 20, 100, 50));

        BOOST_TEST(button1.is_enabled());
        button1.disable();
        BOOST_TEST(!button1.is_enabled());
        button1.enable();
        BOOST_TEST(button1.is_enabled());
    }
}

template <class Widget>
void test_checkbox(ui::widget parent)
{
    Widget checkbox(parent, "Checkbox");
    BOOST_TEST(checkbox.is_unchecked());
    BOOST_TEST(!checkbox.is_checked());
    BOOST_TEST(!checkbox.is_indeterminate());
    BOOST_TEST_EQ(checkbox.tribool(), false);
    BOOST_TEST(!boost::indeterminate(checkbox.tribool()));
    BOOST_TEST(checkbox.optional());
    BOOST_TEST_EQ(*checkbox.optional(), false);

    checkbox.check();
    BOOST_TEST(!checkbox.is_unchecked());
    BOOST_TEST(checkbox.is_checked());
    BOOST_TEST(!checkbox.is_indeterminate());
    BOOST_TEST_EQ(checkbox.tribool(), true);
    BOOST_TEST(!boost::indeterminate(checkbox.tribool()));
    BOOST_TEST(checkbox.optional());
    BOOST_TEST_EQ(*checkbox.optional(), true);

    checkbox.uncheck();
    BOOST_TEST(checkbox.is_unchecked());
    BOOST_TEST(!checkbox.is_checked());
    BOOST_TEST(!checkbox.is_indeterminate());
    BOOST_TEST_EQ(checkbox.tribool(), false);
    BOOST_TEST(!boost::indeterminate(checkbox.tribool()));
    BOOST_TEST(checkbox.optional());
    BOOST_TEST_EQ(*checkbox.optional(), false);

    checkbox.indeterminate();
    BOOST_TEST(!checkbox.is_unchecked());
    BOOST_TEST(!checkbox.is_checked());
    BOOST_TEST(checkbox.is_indeterminate());
    BOOST_TEST(boost::indeterminate(checkbox.tribool()));
    BOOST_TEST(!checkbox.optional());

    checkbox.check();
    BOOST_TEST(!checkbox.is_indeterminate());
    checkbox.check(ui::nullopt);
    BOOST_TEST(checkbox.is_indeterminate());

    checkbox.tribool(true);
    BOOST_TEST_EQ(checkbox.tribool(), true);

    checkbox.tribool(boost::indeterminate);
    BOOST_TEST(boost::indeterminate(checkbox.tribool()));

    checkbox.tribool(false);
    BOOST_TEST_EQ(checkbox.tribool(), false);

    checkbox.optional(true);
    BOOST_TEST(*checkbox.optional());

    checkbox.optional(boost::none);
    BOOST_TEST_EQ(checkbox.optional(), boost::none);

    checkbox.optional(false);
    BOOST_TEST(!*checkbox.optional());
}

void test_textbox(ui::widget parent)
{
    {
        ui::stringbox text0;
        BOOST_TEST(text0.native_handle() == NULL);
    }

    {
        ui::stringbox text1(parent, "Text");
        BOOST_TEST_EQ(text1.text(), "Text");
        text1.text(text1.text() + "!");
        BOOST_TEST_EQ(text1.text(), "Text!");
    }
}

template <class Container>
void test_container_api(Container& container)
{
    BOOST_TEST(container.empty());

    container.push_back("Item C1");
    container.push_back("Item C2");
    BOOST_TEST(!container.empty());
    BOOST_TEST_EQ(container.size(), static_cast<typename Container::size_type>(2));

    BOOST_TEST_EQ(container[0], "Item C1");
    BOOST_TEST_EQ(container.at(1), "Item C2");
    BOOST_TEST_THROWS(container.at(2), std::out_of_range);
    BOOST_TEST_THROWS(container.at(-1), std::out_of_range);

    container.assign(5, "five");
    BOOST_TEST_EQ(container.size(), static_cast<typename Container::size_type>(5));
    BOOST_TEST_EQ(container.at(4), "five");

    static const char* strs[] = { "char*" };
    container.assign(strs, strs + SIZEOF(strs));
    BOOST_TEST_EQ(container.size(), static_cast<typename Container::size_type>(1));
    BOOST_TEST_EQ(container.at(0), "char*");

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    container.assign({ "initializer_list" });
    BOOST_TEST_EQ(container.size(), static_cast<typename Container::size_type>(1));
    BOOST_TEST_EQ(container.at(0), "initializer_list");
#endif

    container.clear();
    BOOST_TEST(container.empty());
    BOOST_TEST_EQ(container.size(), static_cast<typename Container::size_type>(0));
}

template <class Widget>
void test_stringsbox(ui::widget parent)
{
    {
        Widget sw;
        BOOST_TEST(sw.native_handle() == NULL);
    }

    {
        Widget sw(parent);
        BOOST_TEST(sw.empty());
        BOOST_TEST_EQ(sw.size(), 0);

        BOOST_TEST(sw.native_handle() != NULL);
        BOOST_TEST(Widget(sw).native_handle() == sw.native_handle());
        BOOST_TEST(ui::widget(sw).native_handle() == sw.native_handle());
    }
    {
        std::vector<ui::uistring> v;
        v.push_back("Item V1");
        v.push_back(L"Item V2");
        Widget sw(parent, v);
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 2);
    }
    {
        std::vector<ui::uistring> v;
        v.push_back(L"Item V1");
        Widget sw(parent, v.begin(), v.end());
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 1);
    }
    {
        static const char* strs[] =
            { "Item S1", "Item S2", "Item S3" };
        Widget sw(parent, strs);
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 3);

        sw.clear();
        sw.assign(strs);
        BOOST_TEST_EQ(sw.size(), 3);

        Widget sw2(parent, strs, strs + SIZEOF(strs));
        BOOST_TEST_EQ(sw2.size(), 3);

        sw = sw2;
    }
    {
        std::list<std::wstring> l;
        l.push_back(L"Item L1");
        Widget sw(parent, l);
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 1);

        sw.clear();
        sw.assign(l);
        BOOST_TEST_EQ(sw.size(), 1);
    }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    {
        Widget sw(parent, { ui::uistring("Item 1") });
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 1);
    }
    {
        Widget sw(parent, { "Item 1" });
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 1);
    }
    {
        Widget sw(parent, { L"Item 1" });
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 1);
    }
#endif

    {
        std::vector<std::string> vec;
        test_container_api(vec);

        Widget sw(parent);
        test_container_api(sw);
    }
}

void test_progressbar(ui::widget parent)
{
    {
        ui::hprogressbar pb(parent);
        BOOST_TEST_EQ(pb.value(), 0);
        BOOST_TEST_EQ(pb.max(), 100);
        pb.value(0);
        pb.value(100);
        BOOST_TEST_THROWS(pb.value(-1), std::out_of_range);
        BOOST_TEST_THROWS(pb.value(101), std::out_of_range);
    }
    {
        ui::hprogressbar pb(parent, 200, 1000);
        BOOST_TEST_EQ(pb.value(), 200);
        BOOST_TEST_EQ(pb.max(), 1000);
    }
    BOOST_TEST_THROWS(ui::vprogressbar(parent, 101), std::out_of_range);
    BOOST_TEST_THROWS(ui::hprogressbar(parent, 50, 40), std::out_of_range);
}

void test_slider(ui::widget parent)
{
    {
        ui::hslider sl(parent);
        BOOST_TEST_EQ(sl.value(), 0);
        BOOST_TEST_EQ(sl.min(), 0);
        BOOST_TEST_EQ(sl.max(), 100);
    }
    {
        ui::vslider sl(parent, -200, -500, 1000);
        BOOST_TEST_EQ(sl.value(), -200);
        BOOST_TEST_EQ(sl.min(), -500);
        BOOST_TEST_EQ(sl.max(), 1000);
    }
    BOOST_TEST_THROWS(ui::hslider(parent, 101), std::out_of_range);
    BOOST_TEST_THROWS(ui::hslider(parent, 10, 20, 40), std::out_of_range);
    ui::hslider(parent, -30, -40, -20);
}

int ui_main()
{
    ui::dialog dlg("Title");

    test_dialog(dlg);
    test_canvas(dlg);
    test_button(dlg);
    test_checkbox<ui::checkbox>(dlg);
    test_checkbox<ui::tristate_checkbox>(dlg);
    test_textbox(dlg);
    test_stringsbox<ui::choice>(dlg);
    test_stringsbox<ui::combobox>(dlg);
    test_stringsbox<ui::listbox>(dlg);
    test_progressbar(dlg);
    test_slider(dlg);

    BOOST_TEST(!ui::getloc().name().empty());

    //dlg.show_modal();

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
