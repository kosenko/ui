// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui/color.hpp>
#include <boost/ui/color_io.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

#include <stdexcept>

namespace ui = boost::ui;

int cpp_main(int argc, char* argv[])
{
    BOOST_TEST_EQ(ui::color::rgba255(0, 0, 0, 0), ui::color());
    BOOST_TEST_EQ(ui::color::rgba255(0, 0, 0, 255), ui::color::black);
    BOOST_TEST_EQ(ui::color::rgb255(0xff, 0, 0), ui::color::red);
    BOOST_TEST_NE(ui::color::blue, ui::color::red);

    BOOST_TEST_EQ(ui::color::rgba1(1, 0.25, 0.5, 0.75),
                  ui::color::rgba255(255, 64, 128, 191));

    BOOST_TEST_EQ(ui::color::olive.red1(), 128. / 255);
    BOOST_TEST_EQ(ui::color::olive.green1(), 128. / 255);
    BOOST_TEST_EQ(ui::color::olive.blue1(), 0);
    BOOST_TEST_EQ(ui::color::olive.alpha1(), 1);

    BOOST_TEST_EQ(ui::color::navy.red1(), 0);
    BOOST_TEST_EQ(ui::color::navy.green1(), 0);
    BOOST_TEST_EQ(ui::color::navy.blue1(), 128. / 255);
    BOOST_TEST_EQ(ui::color::navy.alpha1(), 1);

    BOOST_TEST_THROWS(ui::color::rgb1(2, 0, 0), std::out_of_range);
    BOOST_TEST_THROWS(ui::color::rgb1(0, -0.5, 0), std::out_of_range);

    return boost::report_errors();
}
