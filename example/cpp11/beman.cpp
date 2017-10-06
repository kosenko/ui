// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// http://isocpp.org/files/papers/n3791.html
// Beman's challenge:
// "Display Hello C++ World in a window and allow the user to drag that text
// around inside the window with a program that is only slightly more complex
// that the traditional hello world program."

#include <boost/ui.hpp>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg("Boost.UI Beman's challenge");

    ui::canvas canvas(dlg);

    ui::point paint_pos(20, 20);
    auto repaint = [&]
    {
        canvas.painter()
            .clear_rect(0, 0, canvas.width(), canvas.height())
            .font(canvas.font())
            .fill_text("Hello C++ World", paint_pos)
            ;
    };

    ui::point drag_start_pos;
    canvas
        .on_resize(repaint)
        .on_left_mouse_down_event([&](ui::mouse_event& e)
        {
            drag_start_pos = e.pos();
        })
        .on_mouse_drag_event([&](ui::mouse_event& e)
        {
            paint_pos += e.pos() - drag_start_pos;
            repaint();

            drag_start_pos = e.pos();
        })
        ;

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
