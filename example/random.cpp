// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Draw normal distribution graph using C++11 or Boost.Random.

#include <boost/ui.hpp>
#include <boost/bind.hpp>

#include <boost/math/special_functions/round.hpp>
#include <map>

#if !defined(BOOST_NO_CXX11_HDR_RANDOM)
#include <random>
namespace random_ns = std;
#else
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>
namespace random_ns = boost::random;
#endif

namespace ui = boost::ui;

class random_dialog : public ui::dialog
{
    typedef random_dialog this_type;

public:
    random_dialog();

private:
    void draw();

    ui::canvas m_canvas;
};

random_dialog::random_dialog() : ui::dialog(
#if !defined(BOOST_NO_CXX11_HDR_RANDOM)
    "C++11 "
#else
    "Boost."
#endif
    "Random + Boost.UI example")
{
    m_canvas.create(*this)
        .tooltip("Normal distribution")
        .on_resize(boost::bind(&this_type::draw, this))
        .on_left_mouse_up(boost::bind(&this_type::draw, this))
        ;
}

void random_dialog::draw()
{
    random_ns::random_device rd;
    random_ns::mt19937 generator(rd());

    random_ns::normal_distribution<> distribution(0, 10);

    typedef std::map<int, int> histogram_type;
    histogram_type histogram;
    static const int repeats = 1000;
    for ( int n = 0; n < repeats; ++n )
    {
        ++histogram[boost::math::iround( distribution(generator) )];
    }

    ui::painter painter = m_canvas.painter();
    painter.clear_rect(0, 0, m_canvas.width(), m_canvas.height());
    painter.translate(m_canvas.width() / 2, m_canvas.height()).scale(4, -4);
    for ( histogram_type::const_iterator iter = histogram.begin();
         iter != histogram.end(); ++iter )
    {
        const double x = iter->first;
        const double y = 1000.0 * iter->second / repeats;

        if ( iter == histogram.begin() )
            painter.move_to(x, y);
        else
            painter.line_to(x, y);
    }
    painter.stroke_color(ui::color::blue).stroke();
}

int ui_main()
{
    random_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
