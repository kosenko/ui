// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui.hpp>
#include <fstream>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

namespace ui = boost::ui;

int ui_main(int argc, char* argv[])
{
    ui::image img;
    BOOST_TEST(!img.valid());
    BOOST_TEST_THROWS(img.width(), std::runtime_error);
    BOOST_TEST_THROWS(img.height(), std::runtime_error);

    if ( argc < 2 )
        return 1;

    std::ifstream fs(argv[1]);
    BOOST_TEST(fs);

    img.load(fs);
    BOOST_TEST(img.valid());
    BOOST_TEST_EQ(img.width(), 16);
    BOOST_TEST_EQ(img.height(), 16);

    std::istringstream ss;
    BOOST_TEST_THROWS(img.load(fs), std::runtime_error);
    BOOST_TEST(!img.valid());

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    //return ui_main(argc, argv);
    return ui::entry(argc, argv, &ui_main);
}
