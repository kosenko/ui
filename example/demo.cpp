// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Sandbox for testing all Boost.UI features.

#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>
#include <boost/version.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/predef.h>

namespace ui = boost::ui;

namespace utility {

void on_handler(const char* class_name,
                const char* event_name)
{
    ui::log().spaces() << class_name << event_name;
}

boost::function<void()>
make_handler(const char* class_name, const char* event_name)
{
    return boost::bind(&on_handler, class_name, event_name);
}

template <class Event>
void on_event_handler(Event&,
                      const char* class_name,
                      const char* event_name)
{
    on_handler(class_name, event_name);
}

template <>
void on_event_handler<ui::key_event>(ui::key_event& e,
                                     const char* class_name,
                                     const char* event_name)
{
    ui::log().spaces() << class_name << event_name
        << e.key_code() << e.get_char()
        << static_cast<char>(e.get_char())
        << (e.ctrl()  ? "ctrl"  : "")
        << (e.shift() ? "shift" : "")
        << (e.alt()   ? "alt"   : "")
        << (e.meta()  ? "meta"  : "");
}

template <>
void on_event_handler<ui::mouse_event>(ui::mouse_event& e,
                                       const char* class_name,
                                       const char* event_name)
{
    ui::log().spaces() << class_name << event_name << e.x() << e.y()
        << (e.left()   ? "left"   : "")
        << (e.right()  ? "right"  : "")
        << (e.middle() ? "middle" : "");
}

template <>
void on_event_handler<ui::wheel_event>(ui::wheel_event& e,
                                       const char* class_name,
                                       const char* event_name)
{
    ui::log().spaces() << class_name << event_name << e.x() << e.y()
        << (e.left()   ? "left"   : "")
        << (e.right()  ? "right"  : "")
        << (e.middle() ? "middle" : "")
        << (e.horizontal() ? "horizontal" : "vertical")
        << (e.horizontal() ? e.delta_x() : e.delta_y());
}

template <>
void on_event_handler<ui::index_event>(ui::index_event& e,
                                       const char* class_name,
                                       const char* event_name)
{
    ui::log().spaces() << class_name << event_name << e.index();
}

template <class Event>
boost::function<void(Event&)>
make_event_handler(const char* class_name, const char* event_name)
{
    return boost::bind(&on_event_handler<Event>, _1, class_name, event_name);
}

} // namespace utility

class demo_frame : public ui::frame
{
    typedef demo_frame this_type;

public:
    demo_frame(int page);

private:
    static void on_press_me();
    static void on_log();

    void on_slide();
    ui::hprogressbar m_progressbar;
    ui::hslider m_slider;

    void on_date_change();
    ui::date_picker m_date_picker;

    void on_time_change();
    ui::time_picker m_time_picker;

    void on_canvas_resize();
    void on_canvas_mouse_draw(ui::mouse_event& e);
    void on_canvas_context_menu(ui::mouse_event& e);
    ui::canvas m_canvas;
};

demo_frame::demo_frame(int page) : ui::frame("Boost.UI Demo")
{
    ui::notebook main_notebook(*this);

    ui::panel layout_panel(main_notebook);
    main_notebook.append_page(layout_panel, "Layout");


    ui::group_box fixed_panel(layout_panel, "Fixed layout");

    ui::button(fixed_panel, "&Press me")
        .on_press(&on_press_me)
        .tooltip("Display environment information")
        .move(5, 5);

    ui::button(fixed_panel, "Show &logs")
        .on_press(&on_log)
        .move(5, 35).resize(80, 100);

    ui::button(fixed_panel, "&Beep")
        .on_press(&ui::beep)
        .move(5, 140);

    ui::button(fixed_panel, "&Close")
        .on_press(&this_type::close, this)
        .move(5, 170);

    ui::box_layout test_layout = ui::vbox()
        << ui::button(layout_panel, "Left").layout().left()
        << ui::button(layout_panel, "Right").layout().right()
        << ui::button(layout_panel, "Center").layout().center()
        << ui::hline(layout_panel).layout().justify()
        << ui::button(layout_panel, "Justify").layout().justify()
        << ui::button(layout_panel, "Stretch, disabled").disable()
            .layout().justify().stretch()
        << ui::button(layout_panel, "Hidden").hide()
        << ( ui::hbox().layout().stretch(2)
            << ui::button(layout_panel, "Top").layout().top()
            << ui::button(layout_panel, "Center").layout().center()
            << ui::button(layout_panel, "Bottom").layout().bottom()
            << ui::vline(layout_panel).layout().justify()
            << ui::button(layout_panel, "Justify").layout().justify()
           )
        ;

    fixed_panel << ui::label().text("Cached label").move(5, 210);

    ui::hbox(layout_panel)
        << fixed_panel.layout().justify()
        << test_layout.layout().justify().stretch()
        ;


    ui::panel widgets_panel(main_notebook);
    main_notebook.append_page(widgets_panel, "Widgets");

    ui::hbox(widgets_panel)
        << ( ui::vbox().layout().justify().stretch()
            << ( ui::hbox().layout().justify()
                << ui::label(widgets_panel, "label")
                << ui::layout::item().stretch()
                << ui::hyperlink(widgets_panel, "http://www.boost.org/", "Boost")
                << ui::image_widget(widgets_panel, ui::image::xdg("go-up", 24, 24))
               )
            << ui::button(widgets_panel, "button")
                .on_press(utility::make_handler("button", "press"))
                .layout().justify()
            << ( ui::hbox().layout().justify()
                << ui::check_box(widgets_panel, "check_box")
                    .indeterminate()
                    .on_toggle(utility::make_handler("check_box", "toggle"))
                    .layout().stretch()
                << ui::tri_state_check_box(widgets_panel, "tri_state_check_box")
                    .indeterminate()
                    .on_toggle(utility::make_handler("tri_state_check_box", "toggle"))
                    .layout().stretch()
               )
            << ui::hline(widgets_panel).layout().justify()
            << ui::string_box(widgets_panel, "string_box")
                .on_edit(utility::make_handler("string", "edit"))
                .layout().justify()
            << ui::password_box(widgets_panel, "123456")
                .on_edit(utility::make_handler("password_box", "edit"))
                .layout().justify()
            << ui::text_box(widgets_panel, "text_box")
                .on_edit(utility::make_handler("text", "edit"))
                .layout().justify().stretch()
            << m_progressbar.create(widgets_panel, 50)
                .layout().justify()
            << m_slider.create(widgets_panel, 50)
                .on_slide(boost::bind(&this_type::on_slide, this))
                .on_slide(utility::make_handler("slider", "slide"))
                .on_slide_end(utility::make_handler("slider", "slide end"))
                .layout().justify()
           )
        << ( ui::vbox().layout().justify().stretch()
            << ui::list_box(widgets_panel,
                           boost::assign::list_of("list_box 1")("list_box 2")("list_box 3"))
                .on_select_event(utility::make_event_handler<ui::index_event>("list_box", "select"))
                .on_activate_event(utility::make_event_handler<ui::index_event>("list_box", "activate"))
                .select(0).layout().justify().stretch()
            << ui::choice(widgets_panel,
                          boost::assign::list_of("choice 1")("choice 2")("choice 3"))
                .on_select_event(utility::make_event_handler<ui::index_event>("list_box", "select"))
                .select(1)
                .layout().justify()
            << ui::combo_box(widgets_panel, "Default combo_box text",
                             boost::assign::list_of("combo_box 1")("combo_box 2")("combo_box 3"))
                .on_select_event(utility::make_event_handler<ui::index_event>("list_box", "select"))
                .select(2)
                .layout().justify()
           )
        ;

    ui::panel datetime_panel(main_notebook);
    main_notebook.append_page(datetime_panel, "Date and time");

    ui::vbox(datetime_panel)
        << m_date_picker.create(datetime_panel)
            .on_change(utility::make_handler("date picker", "change"))
            .on_change(boost::bind(&this_type::on_date_change, this))
        << m_time_picker.create(datetime_panel)
            .on_change(utility::make_handler("time picker", "change"))
            .on_change(boost::bind(&this_type::on_time_change, this))
        ;

    ui::web_widget web_widget_panel(main_notebook);
    if ( web_widget_panel.native_valid() )
    {
        main_notebook.append_page(web_widget_panel, "WebWidget");
        web_widget_panel.html("<h1>Hello</h1>See "
            "<a href=\"http://boost.org/\">Boost</a> libraries, "
            "<a href=\"http://isocpp.org/\">ISO C++</a>, "
            "<a href=\"http://en.wikipedia.org/\">Wikipedia</a>, "
            "<a href=\"http://www.w3.org/\">W3C</a> and "
            "<a href=\"http://google.com/\">Google</a>"
            );
        //web_widget_panel.load("http://boost.org/");
    }

    m_canvas.create(main_notebook)
        .on_resize(boost::bind(&this_type::on_canvas_resize, this))
        .on_key_press_event(utility::make_event_handler<ui::key_event>("canvas", "key press"))
        .on_key_down_event(utility::make_event_handler<ui::key_event>("canvas", "key down"))
        .on_key_up_event(utility::make_event_handler<ui::key_event>("canvas", "key up"))
        .on_left_mouse_down_event(utility::make_event_handler<ui::mouse_event>("canvas", "left mouse down"))
        .on_left_mouse_up_event(utility::make_event_handler<ui::mouse_event>("canvas", "left mouse up"))
        .on_right_mouse_down_event(utility::make_event_handler<ui::mouse_event>("canvas", "right mouse down"))
        .on_right_mouse_up_event(utility::make_event_handler<ui::mouse_event>("canvas", "right mouse up"))
        .on_middle_mouse_down_event(utility::make_event_handler<ui::mouse_event>("canvas", "middle mouse down"))
        .on_middle_mouse_up_event(utility::make_event_handler<ui::mouse_event>("canvas", "middle mouse up"))
        .on_left_mouse_double_click_event(utility::make_event_handler<ui::mouse_event>("canvas", "left mouse double click"))
        .on_right_mouse_double_click_event(utility::make_event_handler<ui::mouse_event>("canvas", "right mouse double click"))
        .on_middle_mouse_double_click_event(utility::make_event_handler<ui::mouse_event>("canvas", "middle mouse double click"))
        //.on_mouse_move_event(utility::make_event_handler<ui::mouse_event>("canvas", "mouse move"))
        .on_mouse_drag_event(utility::make_event_handler<ui::mouse_event>("canvas", "mouse drag"))
        .on_mouse_enter_event(utility::make_event_handler<ui::mouse_event>("canvas", "mouse enter"))
        .on_mouse_leave_event(utility::make_event_handler<ui::mouse_event>("canvas", "mouse leave"))
        .on_context_menu_event(utility::make_event_handler<ui::mouse_event>("canvas", "context menu"))
        .on_mouse_wheel_event(utility::make_event_handler<ui::wheel_event>("canvas", "mouse wheel"))
        .on_mouse_drag_event(boost::bind(&this_type::on_canvas_mouse_draw, this, _1))
        .on_context_menu_event(boost::bind(&this_type::on_canvas_context_menu, this, _1))
        ;
    main_notebook.append_page(m_canvas, "Canvas");

    main_notebook.current_page(page);

    resize(600, 400);
}

void demo_frame::on_press_me()
{
    std::ostringstream info;
    info << "Button pressed";

    info << "\n\nBoost version " << BOOST_VERSION / 100000
        << '.' << BOOST_VERSION / 100 % 1000
        << '.' << BOOST_VERSION % 100;

#ifdef NDEBUG
    info << "\nRelease";
#else
    info << "\nDebug";
#endif

#if defined(BOOST_UI_DYN_LINK) && BOOST_UI_DYN_LINK
    info << "\nDynamic Boost.UI link";
#endif

#if defined(BOOST_UI_STATIC_LINK) && BOOST_UI_STATIC_LINK
    info << "\nStatic Boost.UI link";
#endif

    info << "\nArchitecture: " <<
#if BOOST_ARCH_X86_64
        "x86_64"
#elif BOOST_ARCH_X86_32
        "x86_32"
#else
        "?"
#endif
        << ", sizeof(size_t) == " << sizeof(size_t)
        << ", sizeof(long) == " << sizeof(long)
        << ", sizeof(wchar_t) == " << sizeof(wchar_t)
        ;

    info << "\nPlatform: " << BOOST_PLATFORM;
    info << "\nCompiler: " << BOOST_COMPILER;
    info << "\nstdlib: " << BOOST_STDLIB;

    info << "\n__cplusplus = " << __cplusplus;
    info << "\n__FILE__ = " << __FILE__;
    info << "\n__DATE__ = " << __DATE__;
    info << "\n__TIME__ = " << __TIME__;

#ifdef _MSC_VER
    info << "\n_MSC_VER = " << _MSC_VER;
#endif

#ifdef BOOST_NO_CXX11_CHAR16_T
    info << "\nNO_CXX11_CHAR16_T";
#else
    info << "\nCXX11_CHAR16_T";
#endif

#ifdef BOOST_NO_CXX11_CHAR32_T
    info << "\nNO_CXX11_CHAR32_T";
#else
    info << "\nCXX11_CHAR32_T";
#endif

#ifdef BOOST_NO_CXX11_HDR_CHRONO
    info << "\nNO_CXX11_HDR_CHRONO";
#else
    info << "\nCXX11_HDR_CHRONO";
#endif

#ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    info << "\nNO_CXX11_HDR_INITIALIZER_LIST";
#else
    info << "\nCXX11_HDR_INITIALIZER_LIST";
#endif

#ifdef BOOST_NO_CXX11_HDR_FORWARD_LIST
    info << "\nNO_CXX11_HDR_FORWARD_LIST";
#else
    info << "\nCXX11_HDR_FORWARD_LIST";
#endif

#ifdef BOOST_NO_CXX11_HDR_RANDOM
    info << "\nNO_CXX11_HDR_RANDOM";
#else
    info << "\nCXX11_HDR_RANDOM";
#endif

#ifdef BOOST_NO_CXX11_HDR_REGEX
    info << "\nNO_CXX11_HDR_REGEX";
#else
    info << "\nCXX11_HDR_REGEX";
#endif

#ifdef BOOST_NO_CXX11_HDR_THREAD
    info << "\nNO_CXX11_HDR_THREAD";
#else
    info << "\nCXX11_HDR_THREAD";
#endif

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
    info << "\nNO_CXX11_RVALUE_REFERENCES";
#else
    info << "\nCXX11_RVALUE_REFERENCES";
#endif

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    info << "\nNO_CXX11_VARIADIC_TEMPLATES";
#else
    info << "\nCXX11_VARIADIC_TEMPLATES";
#endif

#ifdef BOOST_UI_NO_STD_HASH
    info << "\nNO_STD_HASH";
#else
    info << "\nSTD_HASH";
#endif

    ui::info_dlg(info.str());
}

void demo_frame::on_log()
{
    ui::info_notify("We have started");
    ui::warning_notify("format C: was started");
    ui::error_notify("format C: was finished, system not found");

    if ( !ui::question("Do something?") )
        return;

    std::wstring name = L"John Doe";
    if ( !ui::prompt("Enter your name", "Name", name) )
        return;

    std::wstring password = L"123456";
    if ( !ui::prompt_password("Enter your password", "Password", password) )
        return;

    ui::info_dlg(L"Your name is " + name
        + L" and your password is " + password);
    ui::warning_dlg("Password could be lost");
    ui::error_dlg("Password was lost");

    if ( !ui::confirm("This code throws errors. Are you sure?") )
        return;

    BOOST_ASSERT_MSG(false, "Test assert");

    //ui::log::fatal() << "Fatal error";
    ui::log::error()   << "Error";
    ui::log::warning() << "Warning";
    ui::log::info()    << "Info";
    ui::log::verbose() << "Verbose";
    ui::log::debug()   << "Debug";
    ui::log::trace()   << "Trace";
    ui::log()          << "Default log";

    BOOST_UI_LOG.spaces().quotes() << "Test" << 12 << .34 << L'!';

    std::string().at(0); // Test exception handling
}

void demo_frame::on_slide()
{
    m_progressbar.value(m_slider.value());
}

void demo_frame::on_date_change()
{
    const std::time_t tt = m_date_picker.get_time_t();
    const struct std::tm m = m_date_picker.get_tm();
    BOOST_UI_LOG << std::ctime(&tt) << std::asctime(&m);
}

void demo_frame::on_time_change()
{
    const std::time_t tt = m_time_picker.get_time_t();
    const struct std::tm m = m_time_picker.get_tm();
    BOOST_UI_LOG << std::ctime(&tt) << std::asctime(&m);
}

void demo_frame::on_canvas_resize()
{
    ui::painter painter = m_canvas.painter();

    {
        ui::painter::state_saver state_scope(painter);

        static const double pi = boost::math::constants::pi<double>();

        painter
            .fill_color(ui::colors::green()).stroke_color(ui::colors::red())
            .line_width(2)
            .font(font()).fill_text("Hello", 60, 50)
            .fill_rect(20, 20, 30, 30).clear_rect(30, 30, 10, 10)
            .stroke_rect(20, 20, 30, 30)
            .move_to(20, 60).line_to(20, 90).line_to(50, 90).close_path()
            .move_to(50, 115).arc(35, 115, 15, 0, pi * 1.5)
            .rect(20, 140, 30, 30)
            .stroke().fill()
            .draw_image(ui::image::xdg("edit-cut", 24, 24), 60, 60);

        painter.line_width(5).stroke_color(ui::colors::black());

        int y = 180;
        {
            ui::painter::state_saver line_cap_scope(painter);

            painter.line_cap(ui::line_cap::butt);
            painter.begin_path().move_to(20, y).line_to(50, y).stroke();
            y += 10;

            painter.line_cap(ui::line_cap::round);
            painter.begin_path().move_to(20, y).line_to(50, y).stroke();
            y += 10;

            painter.line_cap(ui::line_cap::square);
            painter.begin_path().move_to(20, y).line_to(50, y).stroke();
            y += 10;
        }
        {
            ui::painter::state_saver line_cap_scope(painter);

            painter.line_join(ui::line_join::round);
            painter.begin_path().move_to(20, y).line_to(50, y).line_to(20, y + 10).stroke();
            y += 20;

            painter.line_join(ui::line_join::bevel);
            painter.begin_path().move_to(20, y).line_to(50, y).line_to(20, y + 10).stroke();
            y += 20;

            painter.line_join(ui::line_join::miter);
            painter.begin_path().move_to(20, y).line_to(50, y).line_to(20, y + 10).stroke();
            y += 20;

            painter.line_width(2).line_join(ui::line_join::bevel);
            const int dashes[] = { 10, 8 };
            painter.line_dash(dashes);
            painter.begin_path().move_to(20, y     ).line_to(50, y)
                                .line_to(20, y + 10).line_to(50, y + 10).stroke();

            painter.line_dash(ui::nullopt);
            const ui::point cp1(50, y + 20),
                            cp2(50, y + 30),
                            cp3(50, y + 40);
            painter.begin_path().move_to(50, y + 10)
                .quadratic_curve_to(cp1, ui::point(20, y + 30))
                .fill_rect(cp1 - ui::size(1, 1), ui::size(2, 2))
                .bezier_curve_to(cp2, cp3, ui::point(20, y + 40))
                .fill_rect(cp2 - ui::size(1, 1), ui::size(2, 2))
                .fill_rect(cp3 - ui::size(1, 1), ui::size(2, 2))
                .stroke();
        }
    }

    painter.translate(0.5, 0.5);
    painter.stroke_rect(10, 10, m_canvas.width() - 20, m_canvas.height() - 20);
}

void demo_frame::on_canvas_mouse_draw(ui::mouse_event& e)
{
    m_canvas.painter()
        .fill_color(ui::colors::red())
        .fill_rect(e.x() - 1, e.y() - 1, 3, 3);
}

void demo_frame::on_canvas_context_menu(ui::mouse_event& e)
{
    (ui::menu()
        << ui::menu::item("&Hello")
        << ui::menu::item("&Test")
    ).popup(m_canvas);
}

int ui_main(int argc, char* argv[])
{
    int page = 1;

    if ( argc == 2 )
    {
        if ( !boost::conversion::try_lexical_convert(argv[1], page) )
            page = 1;
    }
    else if ( argc > 1 )
    {
        for ( int i = 0; i < argc; i++ )
            ui::log().spaces() << i << "argument" << argv[i];
    }

    demo_frame(page).show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
