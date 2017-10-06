// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Re-implemented GUI examples from
// "Programming -- Principles and Practice Using C++" book by Bjarne Stroustrup

#include <boost/ui.hpp>
#include <boost/math/constants/constants.hpp>

namespace ui = boost::ui;

void draw_axis(ui::painter& painter, const ui::point& a, const ui::point& b)
{
    painter.begin_path();
    painter.move_to(a).line_to(b).stroke();

    const int number_of_notches = 10;
    const ui::size dist = (b - a) / number_of_notches;

    for ( int i = 1; i <= number_of_notches; i++ )
    {
        const ui::point p = a + i * dist;

        painter.move_to(p);

        if ( a.x() == b.x() )
            painter.line_to(p + ui::size(5, 0));
        else if ( a.y() == b.y() )
            painter.line_to(p + ui::size(0, -5));

        painter.stroke();
    }
}

void draw_function(ui::painter& painter, double (*f)(double),
                   double r1, double r2, const ui::gpoint xy,
                   int count, double xscale, double yscale)
{
    if ( count <= 0 )
        throw std::runtime_error("non-positive graphing count");

    painter.begin_path();

    const double dist = (r2 - r1) / count;

    double r = r1;
    for ( int i = 0; i < count; i++ )
    {
        const ui::gpoint p = xy + ui::gsize(r * xscale, -f(r) * yscale);

        if ( i == 0 )
            painter.move_to(p);

        painter.line_to(p);

        r += dist;
    }

    painter.stroke();
}

void draw_ellipse(ui::painter& painter, const ui::gpoint& center,
                  double width, double height)
{
    static const double pi = boost::math::constants::pi<double>();

    ui::painter::state_saver saver(painter);

    painter
        .translate(center).scale(1, height / width)
        .begin_path().arc(0, 0, width, 0, pi * 2).stroke();
}

int ui_main()
{
    ui::dialog dlg("Canvas");
    dlg.move(100, 100).resize(600, 400);

    ui::canvas canvas(dlg);
    canvas.on_resize([&]
    {
        ui::painter painter = canvas.painter();

        painter.font(canvas.font());
        painter.translate(0.5, 0.5);

        // Axes
        {
            ui::painter::state_saver saver(painter);

            draw_axis(painter, {20, 300}, {300, 300});
            painter.fill_text("x axis", 100, 320);

            painter.stroke_color(ui::color::teal);
            draw_axis(painter, {20, 300}, {20, 20});
            painter.fill_color(ui::color::maroon).fill_text("y axis", 10, 10);
        }

        // Function
        {
            ui::painter::state_saver saver(painter);
            painter.stroke_color(ui::color::blue);
            draw_function(painter, &std::sin, 0, 100, {20, 150}, 1000, 50, 50);
        }

        // Polygon
        {
            ui::painter::state_saver saver(painter);

            painter
                .begin_path()
                .move_to(300, 200).line_to(350, 100).line_to(400, 200).close_path()
                .line_dash({ 12, 4 }).line_width(4)
                .stroke_color(ui::color::red).stroke();
        }

        {
            ui::painter::state_saver saver(painter);

            // Rectangle
            painter
                .fill_color(ui::color::yellow)
                .fill_rect(  200, 200, 100, 50)
                .stroke_rect(200, 200, 100, 50);

            // Closed polyline
            painter
                .begin_path().move_to(100, 50).line_to(200, 50).line_to(200, 100)
                .line_to(100, 100).line_to(50, 75).close_path()
                .fill_color(ui::color::green).fill()
                .line_dash({ 6, 2 }).line_width(2)
                .stroke();
        }

        // Text
        painter.fill_text("Hello, graphical world!", 150, 150);

        // Image
        painter.draw_image(ui::image::xdg("dialog-information", 24, 24), 200, 250);

        // And much more

        static const double pi = boost::math::constants::pi<double>();
        static const ui::gpoint center(100, 200);

        painter.begin_path().arc(center, 50, 0, pi * 2).stroke();

        {
            ui::painter::state_saver saver(painter);
            painter.stroke_color(ui::color::maroon);
            draw_ellipse(painter, center, 75, 25);
        }

        painter
            .begin_path().move_to(center + ui::gsize(-5, -5))
                         .line_to(center + ui::gsize( 5,  5)).stroke()
            .begin_path().move_to(center + ui::gsize(-5,  5))
                         .line_to(center + ui::gsize( 5, -5)).stroke()
            ;

        std::ostringstream oss;
        oss << "window size: " << dlg.width() << "*" << dlg.height();
        painter.fill_text(oss.str(), 100, 20);

        dlg.title("Canvas #12");
    });

    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
