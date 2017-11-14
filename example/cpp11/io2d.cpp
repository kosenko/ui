// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Re-implemented examples from P0267R6 C++ Standard proposal
// "A Proposal to Add 2D Graphics Rendering and Display to C++"
// (io2d library)
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0267r6.pdf

#include <boost/ui.hpp>
#include <boost/math/constants/constants.hpp>

namespace ui = boost::ui;

int ui_main()
{
    ui::dialog dlg("io2d examples implementation");
    dlg.resize(700, 500);

    ui::canvas canvas(dlg);
    canvas.on_resize([&]
    {
        ui::painter painter = canvas.painter();
        painter.translate(0.5, 0.5);

        painter.fill_rect(0, 0, 600, 400);
        painter.stroke_color(ui::color::white)
               .fill_color(  ui::color::white);

        // Example 1
        {
            painter.begin_path()
                .move_to(80, 20).line_to(220, 20).line_to(280, 180).line_to(20, 180)
                .close_path().stroke();
        }

        painter.translate(300, 0);

        // Example 2
        {
            ui::painter::state_saver state(painter);

            painter.line_width(10).begin_path()
                .move_to(20, 20).line_to(120, 20).line_to(120, 160).line_to(20, 160).line_to(20, 20)
                .stroke();
            painter.translate(160, 0)
                .move_to(20, 20).line_to(120, 20).line_to(120, 160).line_to(20, 160).line_to(20, 20)
                .close_path().stroke();
        }

        painter.translate(-300, 200);

        // Example 3
        {
            painter.begin_path()
                .move_to(20,  20).quadratic_curve_to(80,  140, 140, 20)
                .move_to(160, 20).quadratic_curve_to(220, 140, 280, 20).close_path()
                .stroke();
            painter.begin_path()
                .move_to( 20, 150).bezier_curve_to( 60, 30, 100, 270, 140, 150)
                .move_to(160, 150).bezier_curve_to(220, 30, 260, 270, 300, 150).close_path()
                .stroke();
        }

        painter.translate(300, 0);

        // Example 4
        {
            {
                ui::painter::state_saver state(painter);

                static const double pi = boost::math::constants::pi<double>();

                painter.line_width(10).translate(85, 100).scale(.9, 1.1).begin_path()
                    .arc(0, 0, 50, pi / 4, pi * 7 / 4)
                    .stroke();
            }

            auto drawPlus = [&painter]()
            {
                painter.begin_path()
                    .move_to(130, 105).line_to(130,  95).line_to(155,  95)
                    .line_to(155,  70).line_to(165,  70).line_to(165,  95)
                    .line_to(190,  95).line_to(190, 105).line_to(165, 105)
                    .line_to(165, 130).line_to(155, 130).line_to(155, 105)
                    .fill();
            };

            drawPlus();

            painter.translate(80, 0);
            drawPlus();
        }
    });

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
