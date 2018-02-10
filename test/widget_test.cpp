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

void test_parent(ui::window& parent)
{
    BOOST_TEST(parent.native_handle() != NULL);
    BOOST_TEST(parent.native_valid());

    BOOST_TEST(!parent.is_shown());

    BOOST_TEST_EQ(parent.title(), "Title");
    parent.title(parent.title() + " test");
    BOOST_TEST_EQ(parent.title(), "Title test");
}

void my_handler()
{
    BOOST_UI_LOG;
}

void my_handler_1(int value)
{
    BOOST_UI_LOG << value;
}

void my_handler_event(ui::mouse_event& e)
{
    BOOST_UI_LOG.spaces() << e.x() << e.y();
}

void my_handler_event_1(int value, ui::mouse_event& e)
{
    BOOST_UI_LOG.spaces() << value << e.x() << e.y();
}

class my_handlers
{
public:
    my_handlers(int value) : m_value(value) {}
    void my_handler()
    {
        BOOST_UI_LOG << m_value;
    }
    void my_handler_event(ui::mouse_event& e)
    {
        BOOST_UI_LOG.spaces() << m_value << e.x() << e.y();
    }

private:
    int m_value;
};

template <class TWindow>
void test_window(ui::window& parent)
{
    TWindow win_not_created;
    BOOST_TEST(!win_not_created.native_valid());
    BOOST_TEST(win_not_created.native_handle() == NULL);

    TWindow win("My title");
    BOOST_TEST_EQ(win.title(), "My title");
    win.title(win.title() + " test!");
    BOOST_TEST_EQ(win.title(), "My title test!");

    BOOST_TEST(!win.is_shown());
    win.show();
    BOOST_TEST(win.is_shown());
    win.hide();
    BOOST_TEST(!win.is_shown());

    win.on_mouse_drag(&my_handler);
    win.on_mouse_drag(&my_handler_1, 2);
    win.on_mouse_drag_event(&my_handler_event);
    win.on_mouse_drag_event(&my_handler_event_1, 3);
    my_handlers a(10);
    win.on_mouse_drag(&my_handlers::my_handler, &a);
    win.on_mouse_drag_event(&my_handlers::my_handler_event, &a);

    //win.show_modal();
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

        BOOST_TEST_EQ(button1.tooltip(), "");
        button1.tooltip("My tooltip");
        BOOST_TEST_EQ(button1.tooltip(), "My tooltip");

        ui::font f = button1.font();
        BOOST_TEST(f.valid());
        f.size_pt(32);
        button1.font(f);
        BOOST_TEST_EQ(button1.font().size_pt(), 32);
    }
}

template <class Widget>
void test_check_box(ui::widget parent)
{
    Widget check_box(parent, "Checkbox");
    BOOST_TEST(check_box.is_unchecked());
    BOOST_TEST(!check_box.is_checked());
    BOOST_TEST(!check_box.is_indeterminate());
    BOOST_TEST_EQ(check_box.tribool(), false);
    BOOST_TEST(!boost::indeterminate(check_box.tribool()));
    BOOST_TEST(check_box.optional());
    BOOST_TEST_EQ(*check_box.optional(), false);

    check_box.check();
    BOOST_TEST(!check_box.is_unchecked());
    BOOST_TEST(check_box.is_checked());
    BOOST_TEST(!check_box.is_indeterminate());
    BOOST_TEST_EQ(check_box.tribool(), true);
    BOOST_TEST(!boost::indeterminate(check_box.tribool()));
    BOOST_TEST(check_box.optional());
    BOOST_TEST_EQ(*check_box.optional(), true);

    check_box.uncheck();
    BOOST_TEST(check_box.is_unchecked());
    BOOST_TEST(!check_box.is_checked());
    BOOST_TEST(!check_box.is_indeterminate());
    BOOST_TEST_EQ(check_box.tribool(), false);
    BOOST_TEST(!boost::indeterminate(check_box.tribool()));
    BOOST_TEST(check_box.optional());
    BOOST_TEST_EQ(*check_box.optional(), false);

    check_box.indeterminate();
    BOOST_TEST(!check_box.is_unchecked());
    BOOST_TEST(!check_box.is_checked());
    BOOST_TEST(check_box.is_indeterminate());
    BOOST_TEST(boost::indeterminate(check_box.tribool()));
    BOOST_TEST(!check_box.optional());

    check_box.check();
    BOOST_TEST(!check_box.is_indeterminate());
    check_box.check(ui::nullopt);
    BOOST_TEST(check_box.is_indeterminate());

    check_box.tribool(true);
    BOOST_TEST_EQ(check_box.tribool(), true);

    check_box.tribool(boost::indeterminate);
    BOOST_TEST(boost::indeterminate(check_box.tribool()));

    check_box.tribool(false);
    BOOST_TEST_EQ(check_box.tribool(), false);

    check_box.optional(true);
    BOOST_TEST(*check_box.optional());

    check_box.optional(boost::none);
    BOOST_TEST_EQ(check_box.optional(), boost::none);

    check_box.optional(false);
    BOOST_TEST(!*check_box.optional());
}

template <class Widget>
void test_text(ui::widget parent)
{
    Widget widget(parent, "Text");
    BOOST_TEST(widget.native_handle() != NULL);
    BOOST_TEST_EQ(widget.text(), "Text");
    widget.text(widget.text() + "!");
    BOOST_TEST_EQ(widget.text(), "Text!");
    widget.clear();
    BOOST_TEST_EQ(widget.text(), ui::uistring());
}

void test_text_box(ui::widget parent)
{
    {
        ui::string_box w;
        BOOST_TEST(w.native_handle() == NULL);
    }

    test_text<ui::string_box>(parent);
    test_text<ui::text_box>(parent);
    test_text<ui::password_box>(parent);
    test_text<ui::label>(parent);
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
void test_strings_box(ui::widget parent)
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
        Widget sw(parent, { ui::uistring("Item 1"), ui::uistring("Item 2") });
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 2);
    }
    {
        Widget sw(parent, { "Item 1", "Item 2" });
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 2);
    }
    {
        Widget sw(parent, { L"Item 1", L"Item 2" });
        BOOST_TEST(!sw.empty());
        BOOST_TEST_EQ(sw.size(), 2);
    }
#endif

    {
        std::vector<std::string> vec;
        test_container_api(vec);

        Widget sw(parent);
        test_container_api(sw);
    }
}

void test_progress_bar(ui::widget parent)
{
    {
        ui::hprogress_bar pb(parent);
        BOOST_TEST_EQ(pb.value(), 0);
        BOOST_TEST_EQ(pb.max(), 100);
        pb.value(0);
        pb.value(100);
        BOOST_TEST_THROWS(pb.value(-1), std::out_of_range);
        BOOST_TEST_THROWS(pb.value(101), std::out_of_range);
    }
    {
        ui::hprogress_bar pb(parent, 200, 1000);
        BOOST_TEST_EQ(pb.value(), 200);
        BOOST_TEST_EQ(pb.max(), 1000);
    }
    BOOST_TEST_THROWS(ui::vprogress_bar(parent, 101), std::out_of_range);
    BOOST_TEST_THROWS(ui::hprogress_bar(parent, 50, 40), std::out_of_range);
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

void test_notebook(ui::widget parent)
{
    ui::notebook nb(parent);
    BOOST_TEST_EQ(nb.current_page_index(), -1);

    ui::panel p1(nb);
    nb.append_page(p1, "Test 1");
    BOOST_TEST_EQ(nb.current_page_index(), 0);

    ui::panel p2(nb);
    nb.append_page(p2, "Test 2");
    BOOST_TEST_EQ(nb.current_page_index(), 0);

    nb.current_page(1);
    BOOST_TEST_EQ(nb.current_page_index(), 1);
}

void test_static_widgets(ui::widget parent)
{
    {
        ui::vline w(parent);
        BOOST_TEST(w.native_valid());
    }
    {
        ui::hline w(parent);
        BOOST_TEST(w.native_valid());
    }
    {
        ui::group_box w(parent, "My title");
        BOOST_TEST(w.native_valid());
    }
    {
        ui::hyperlink w(parent, "http://www.boost.org/", "Boost C++ libraries");
        BOOST_TEST(w.native_valid());
    }
    {
        ui::image_widget w(parent, ui::image::xdg("folder", 32, 32));
        BOOST_TEST(w.native_valid());
    }
    {
        ui::image_widget w;
        BOOST_TEST(!w.native_valid());
        w.create(parent).image(ui::image::xdg("folder", 32, 32));
        BOOST_TEST(w.native_valid());
    }
    {
        ui::web_widget w(parent);
        BOOST_TEST(w.native_valid());
        w.load("http://www.boost.org/");
    }
}

int ui_main()
{
    ui::dialog dlg("Title");

    test_parent(dlg);
    test_window<ui::dialog>(dlg);
    test_window<ui::frame>(dlg);
    test_canvas(dlg);
    test_button(dlg);
    test_check_box<ui::check_box>(dlg);
    test_check_box<ui::tri_state_check_box>(dlg);
    test_text_box(dlg);
    test_strings_box<ui::choice>(dlg);
    test_strings_box<ui::combo_box>(dlg);
    test_strings_box<ui::list_box>(dlg);
    test_progress_bar(dlg);
    test_slider(dlg);
    test_notebook(dlg);
    test_static_widgets(dlg);

    BOOST_TEST(!ui::getloc().name().empty());

    //dlg.show_modal();

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
