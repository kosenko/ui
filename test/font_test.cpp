// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui/application.hpp>
#include <boost/ui/font.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

namespace ui = boost::ui;

int ui_main()
{
    BOOST_TEST(!ui::font().valid());
    BOOST_TEST_THROWS(ui::font().name(), std::runtime_error);
    BOOST_TEST_THROWS(ui::font().size_pt(), std::runtime_error);
    BOOST_TEST_THROWS(ui::font().get_family(), std::runtime_error);
    BOOST_TEST_THROWS(ui::font().get_slant(), std::runtime_error);
    BOOST_TEST_THROWS(ui::font().get_weight(), std::runtime_error);

    BOOST_TEST(ui::font::caption().valid());

    BOOST_TEST_THROWS(ui::font(-1, "Arial"), std::out_of_range);
    BOOST_TEST_THROWS(ui::font(-1, ui::font::family::serif), std::out_of_range);

    BOOST_TEST_THROWS(ui::font(12, "Invalid font name"), std::out_of_range);

    {
        const ui::font f(12, "Arial");
        BOOST_TEST(f.valid());
        BOOST_TEST_EQ(f.size_pt(), 12);
        BOOST_TEST_EQ(f.name().string(), "Arial");
        BOOST_TEST(f.get_family() != ui::font::family::monospace);
        BOOST_TEST(f.get_slant()  == ui::font::slant::normal);
        BOOST_TEST(f.get_weight() == ui::font::weight::normal);
    }

    {
        const ui::font f(16, ui::font::family::sans_serif,
            ui::font::slant::italic, ui::font::weight::bold);
        BOOST_TEST(f.valid());
        BOOST_TEST_EQ(f.size_pt(), 16);
        BOOST_TEST(f.get_family() == ui::font::family::sans_serif);
        BOOST_TEST(f.get_slant()  == ui::font::slant::italic);
        BOOST_TEST(f.get_weight() == ui::font::weight::bold);
    }

    {
        ui::font f = ui::font::caption();
        BOOST_TEST_EQ(f.size_pt(14).size_pt(), 14);
        BOOST_TEST_EQ(f.name("Arial").name().string(), "Arial");
        BOOST_TEST(f.set_slant(ui::font::slant::italic).get_slant()
                            == ui::font::slant::italic);
        BOOST_TEST(f.set_weight(ui::font::weight::bold).get_weight()
                             == ui::font::weight::bold);

        BOOST_TEST_THROWS(f.size_pt(-1), std::out_of_range);
        BOOST_TEST_THROWS(f.size_pt(0), std::out_of_range);
        BOOST_TEST_THROWS(f.name("Invalid name XXX"), std::out_of_range);
    }

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
