// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui/coord.hpp>
#include <boost/ui/coord_io.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

#ifdef BOOST_UI_USE_GEOMETRY
#include <boost/geometry/algorithms/equals.hpp>
#endif

#include <iomanip>

namespace ui = boost::ui;

template <class CharT>
void test_stream()
{
    std::basic_ostringstream<CharT> oss_actual;
    oss_actual << ui::point(3, 5);

    std::basic_ostringstream<CharT> oss_expected;
    oss_expected << '(' << '3' << ',' << '5' << ')';
    BOOST_TEST(oss_actual.str() == oss_expected.str());
}

int cpp_main(int argc, char* argv[])
{
    BOOST_TEST_EQ(ui::size(), ui::size(0, 0));
    BOOST_TEST_NE(ui::size(1, 1), ui::size(0, 0));
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    BOOST_TEST_EQ(ui::size({1, -2}), ui::size(1, -2));
#endif
    BOOST_TEST_EQ(ui::size(ui::basic_size<double>(1.9, -1.9)), ui::size(1, -1));
    BOOST_TEST_EQ(2 * ui::size(3, 4), ui::size(6, 8));
    BOOST_TEST_EQ(ui::size(2, 3) * 4, ui::size(8, 12));
    BOOST_TEST_EQ(ui::size(10, 9) / 5, ui::size(2, 1));

    BOOST_TEST_EQ(ui::point(), ui::point(0, 0));
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    //BOOST_TEST_EQ(ui::point({1, -2}), ui::point(1, -2));
#endif
    BOOST_TEST_EQ(ui::point(ui::basic_point<double>(1.9, -1.9)), ui::point(1, -1));
    BOOST_TEST_EQ(ui::point(1, 2), ui::point(1, 2));
    BOOST_TEST_NE(ui::point(1, 1), ui::point(0, 0));

    BOOST_TEST_EQ(ui::point(1, 2) + ui::size(3, 5), ui::point(4, 7));
    BOOST_TEST_EQ(ui::point(1, 2) - ui::size(3, 5), ui::point(-2, -3));
    BOOST_TEST_EQ(ui::point(1, 2) - ui::point(3, 5), ui::size(-2, -3));

    {
        ui::point p(2, 3);
        p += ui::size(4, 6);
        BOOST_TEST_EQ(p, ui::point(6, 9));
    }
    {
        ui::point p(2, 3);
        p -= ui::size(4, 6);
        BOOST_TEST_EQ(p, ui::point(-2, -3));
    }

#ifdef BOOST_UI_USE_GEOMETRY
    typedef boost::geometry::model::d2::point_xy<ui::coord_type> point_xy_coord;
    BOOST_TEST( boost::geometry::equals(static_cast<point_xy_coord>(ui::point(5, 10)),
                                        static_cast<point_xy_coord>(ui::point(5, 10))) );
    BOOST_TEST_EQ(ui::point(point_xy_coord(1, 2)), ui::point(1, 2));
    {
        ui::point p(3, 5);
        BOOST_TEST_EQ(p.get<1>(), 5);
        BOOST_TEST_EQ(boost::geometry::get<0>(static_cast<point_xy_coord>(p)), 3);
    }
#endif
#ifdef BOOST_UI_USE_POLYGON
    ui::point(boost::polygon::point_data<ui::coord_type>(1, 2));
#endif

    {
        std::ostringstream oss;
        oss << std::setprecision(3);
        oss << ui::basic_point<double>(10.1234, -3.1234);
        BOOST_TEST_EQ(oss.str(), "(10.1,-3.12)");
    }

    test_stream<char>();
    test_stream<wchar_t>();
#ifndef BOOST_NO_CXX11_CHAR16_T
    //test_stream<char16_t>();
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    //test_stream<char32_t>();
#endif

    {
#ifdef BOOST_UI_USE_GEOMETRY
        BOOST_TEST_EQ(ui::rect().min_corner().x(), 0);
        BOOST_TEST_EQ(ui::rect().min_corner().y(), 0);
        BOOST_TEST_EQ(ui::rect().max_corner().x(), 0);
        BOOST_TEST_EQ(ui::rect().max_corner().y(), 0);
#endif
        BOOST_TEST_EQ(ui::rect(), ui::rect(0, 0, 0, 0));
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
        //BOOST_TEST_EQ(ui::rect({1, -2, 3, 4}), ui::rect(1, -2, 3, 4));
#endif
        BOOST_TEST_EQ(ui::rect(ui::basic_rect<double>(1.9, -1.9, 2.8, 3.8)),
                      ui::rect(1, -1, 2, 3));

        ui::rect rect(1, 2, 3, 4);
#ifdef BOOST_UI_USE_GEOMETRY
        BOOST_TEST_EQ(rect.min_corner().x(), 1);
        BOOST_TEST_EQ(rect.min_corner().y(), 2);
        BOOST_TEST_EQ(rect.max_corner().x(), 4);
        BOOST_TEST_EQ(rect.max_corner().y(), 6);
#endif
        BOOST_TEST_EQ(rect.x(), 1);
        BOOST_TEST_EQ(rect.y(), 2);
        BOOST_TEST_EQ(rect.width(), 3);
        BOOST_TEST_EQ(rect.height(), 4);
        BOOST_TEST_EQ(rect, ui::rect(1, 2, 3, 4));
        BOOST_TEST_NE(rect, ui::rect());

        BOOST_TEST_EQ(ui::rect(ui::point(1, 2), ui::size(3, 4)), ui::rect(1, 2, 3, 4));
        BOOST_TEST_EQ(ui::rect(ui::point(1, 2), ui::point(3, 4)), ui::rect(1, 2, 2, 2));

        ui::rect inverted_rect(4, 6, -3, -4);
#ifdef BOOST_UI_USE_POLYGON
        BOOST_TEST_EQ(inverted_rect.x(), 1);
        BOOST_TEST_EQ(inverted_rect.y(), 2);
        BOOST_TEST_EQ(inverted_rect.width(), 3);
        BOOST_TEST_EQ(inverted_rect.height(), 4);
#else
        BOOST_TEST_EQ(inverted_rect.x(), 4);
        BOOST_TEST_EQ(inverted_rect.y(), 6);
        BOOST_TEST_EQ(inverted_rect.width(), -3);
        BOOST_TEST_EQ(inverted_rect.height(), -4);
#endif

#ifdef BOOST_UI_USE_POLYGON
        BOOST_TEST_EQ(rect, inverted_rect);
#else
        BOOST_TEST_NE(rect, inverted_rect);
#endif
#ifdef BOOST_UI_USE_GEOMETRY
        typedef boost::geometry::model::box<point_xy_coord>
            rect_type;
        BOOST_TEST(  boost::geometry::equals(static_cast<rect_type>(rect),
                                             static_cast<rect_type>(ui::rect(1, 2, 3, 4))) );
        BOOST_TEST( !boost::geometry::equals(static_cast<rect_type>(rect),
                                             static_cast<rect_type>(inverted_rect)) );
        BOOST_TEST_EQ(ui::rect( rect_type(point_xy_coord(1, 2), point_xy_coord(4, 6)) ),
                      ui::rect(1, 2, 3, 4));
#endif
#ifdef BOOST_UI_USE_POLYGON
        BOOST_TEST_EQ(ui::rect(boost::polygon::rectangle_data<ui::coord_type>(1, 2, 4, 6)),
                      ui::rect(1, 2, 3, 4));
#endif
    }

    return boost::report_errors();
}
