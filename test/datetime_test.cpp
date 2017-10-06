// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_USE_DATE_TIME
#define BOOST_UI_USE_CHRONO

#include <boost/ui.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

#ifdef BOOST_UI_USE_DATE_TIME
#include <boost/date_time/gregorian/gregorian.hpp>
#endif

namespace ui = boost::ui;

static void test_date_time_t(std::time_t actual, std::time_t expected)
{
    const double diff = std::difftime(expected, actual);
    BOOST_TEST(diff <  24 * 60 * 60);
    BOOST_TEST(diff > -24 * 60 * 60);
}

void test_date_picker(ui::widget parent)
{
    ui::date_picker picker(parent);

    // Initial test

    BOOST_TEST_NE(picker.get_time_t(), static_cast<std::time_t>(-1));
    BOOST_TEST(picker.get_time_t() > 365 * 24 * 60 * 60);

    const std::tm t_now = picker.get_tm();
    BOOST_TEST_EQ(t_now.tm_hour, 0);
    BOOST_TEST_EQ(t_now.tm_min, 0);
    BOOST_TEST_EQ(t_now.tm_sec, 0);

    BOOST_TEST_THROWS(picker.set_time_t(static_cast<std::time_t>(-1)), std::out_of_range);

    // Test 2001-02-03

    const std::time_t time_2001_02_03 = 981158400;
    picker.set_time_t(time_2001_02_03); // 2001-02-03
    test_date_time_t(picker.get_time_t(), time_2001_02_03);

    const std::tm t = picker.get_tm();
    BOOST_TEST_EQ(t.tm_year, 101);
    BOOST_TEST_EQ(t.tm_mon, 1);
    BOOST_TEST_EQ(t.tm_mday, 3);
    BOOST_TEST_EQ(t.tm_hour, 0);
    BOOST_TEST_EQ(t.tm_min, 0);
    BOOST_TEST_EQ(t.tm_sec, 0);
    BOOST_TEST_EQ(t.tm_wday, 6);
    BOOST_TEST_EQ(t.tm_yday, 33);

#ifdef BOOST_UI_USE_DATE_TIME
    BOOST_TEST_EQ(picker.gregorian_date(), boost::gregorian::date(2001, 2, 3));
#endif

#ifdef BOOST_UI_USE_CHRONO
    test_date_time_t(boost::chrono::system_clock::to_time_t(picker.boost_system_clock_time_point()), time_2001_02_03);
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    test_date_time_t(std::chrono::system_clock::to_time_t(picker.system_clock_time_point()), time_2001_02_03);
#endif

    picker.set_tm(t);
    test_date_time_t(picker.get_time_t(), time_2001_02_03);

    // Test 1970-02-03

    std::tm t_set = t;

    t_set.tm_year = 70;
    picker.set_tm(t_set);

    {
        const std::tm t_new = picker.get_tm();
        BOOST_TEST_EQ(t_new.tm_year, t_set.tm_year);
        BOOST_TEST_EQ(t_new.tm_mon,  t_set.tm_mon);
        BOOST_TEST_EQ(t_new.tm_mday, t_set.tm_mday);
    }

    test_date_time_t(picker.get_time_t(), 2851200); // 1970-02-03

#ifdef BOOST_UI_USE_DATE_TIME
    BOOST_TEST_EQ(picker.gregorian_date(), boost::gregorian::date(1970, 2, 3));
#endif

#if 0
    // Test 1901-02-03

    t_set.tm_year = 1;
    picker.set_tm(t_set);

    {
        const std::tm t_new = picker.get_tm();
        BOOST_TEST_EQ(t_new.tm_year, t_set.tm_year);
        BOOST_TEST_EQ(t_new.tm_mon,  t_set.tm_mon);
        //BOOST_TEST_EQ(t_new.tm_mday, t_set.tm_mday);
    }

    BOOST_TEST_THROWS(picker.get_time_t(), std::out_of_range);

#ifdef BOOST_UI_USE_DATE_TIME
    //BOOST_TEST_EQ(picker.gregorian_date(), boost::gregorian::date(1901, 2, 3));
#endif
#endif

#ifdef BOOST_UI_USE_DATE_TIME
    // Test 1969-02-03

    picker.gregorian_date(boost::gregorian::date(1969, 2, 3));
    BOOST_TEST_EQ(picker.gregorian_date(), boost::gregorian::date(1969, 2, 3));
#endif

#ifdef BOOST_UI_USE_CHRONO
    picker.system_clock_time_point(boost::chrono::system_clock::from_time_t(time_2001_02_03));
    test_date_time_t(picker.get_time_t(), time_2001_02_03);
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    picker.system_clock_time_point(std::chrono::system_clock::from_time_t(time_2001_02_03 + 7 * 24 * 60 * 60));
    test_date_time_t(picker.get_time_t(), time_2001_02_03 + 7 * 24 * 60 * 60);
#endif
}

void test_time_picker(ui::widget parent)
{
    ui::time_picker picker(parent);

    // Initial test

    BOOST_TEST_NE(picker.get_time_t(), static_cast<std::time_t>(-1));
    BOOST_TEST(picker.get_time_t() >= 0);
    BOOST_TEST(picker.get_time_t() <= 24 * 60 * 60);

    const std::tm t_now = picker.get_tm();
    BOOST_TEST_EQ(t_now.tm_year, 0);
    BOOST_TEST_EQ(t_now.tm_mon, 0);
    BOOST_TEST_EQ(t_now.tm_mday, 0);

    // Test 00:00:00

    picker.set_time_t(0);
    BOOST_TEST_EQ(picker.get_time_t(), 0);

    {
        const std::tm t = picker.get_tm();
        BOOST_TEST_EQ(t.tm_year, 0);
        BOOST_TEST_EQ(t.tm_mon, 0);
        BOOST_TEST_EQ(t.tm_mday, 0);
        BOOST_TEST_EQ(t.tm_hour, 0);
        BOOST_TEST_EQ(t.tm_min, 0);
        BOOST_TEST_EQ(t.tm_sec, 0);
        BOOST_TEST_EQ(t.tm_wday, 0);
        BOOST_TEST_EQ(t.tm_yday, 0);
    }

    picker.set_tm(picker.get_tm());
    BOOST_TEST_EQ(picker.get_time_t(), 0);

#ifdef BOOST_UI_USE_DATE_TIME
    BOOST_TEST_EQ(picker.posix_time_duration(), boost::posix_time::time_duration(0, 0, 0));
    picker.posix_time_duration(picker.posix_time_duration());
    BOOST_TEST_EQ(picker.get_time_t(), 0);
#endif

#ifdef BOOST_UI_USE_CHRONO
    {
        const boost::chrono::seconds d = picker.boost_chrono_duration<int, boost::ratio<1> >();
        BOOST_TEST_EQ(d, boost::chrono::seconds(0));
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    {
        const std::chrono::seconds d = picker.chrono_duration<int, std::ratio<1> >();
        BOOST_TEST(d == std::chrono::seconds(0));
    }
#endif

    // Test 01:02:03

    const time_t time_1_2_3 = ((1 * 60) + 2) * 60 + 3;
    picker.set_time_t(time_1_2_3 + 10 * 24 * 60 * 60);
    BOOST_TEST_EQ(picker.get_time_t(), time_1_2_3);

    {
        const std::tm t = picker.get_tm();
        BOOST_TEST_EQ(t.tm_year, 0);
        BOOST_TEST_EQ(t.tm_mon, 0);
        BOOST_TEST_EQ(t.tm_mday, 0);
        BOOST_TEST_EQ(t.tm_hour, 1);
        BOOST_TEST_EQ(t.tm_min, 2);
        BOOST_TEST_EQ(t.tm_sec, 3);
        BOOST_TEST_EQ(t.tm_wday, 0);
        BOOST_TEST_EQ(t.tm_yday, 0);
    }

#ifdef BOOST_UI_USE_DATE_TIME
    BOOST_TEST_EQ(picker.posix_time_duration(), boost::posix_time::time_duration(1, 2, 3));
#endif

#ifdef BOOST_UI_USE_CHRONO
    {
        const boost::chrono::seconds d = picker.boost_chrono_duration<int, boost::ratio<1> >();
        BOOST_TEST_EQ(d, boost::chrono::seconds(time_1_2_3));
    }
    {
        const boost::chrono::milliseconds d = picker.boost_chrono_duration<int, boost::milli >();
        BOOST_TEST_EQ(d, boost::chrono::milliseconds(time_1_2_3 * 1000));
    }
    {
        typedef boost::chrono::duration< double, boost::chrono::minutes::period > double_minutes;
        const double_minutes d =
            picker.boost_chrono_duration<double_minutes::rep, double_minutes::period >();
        BOOST_TEST_EQ(d, double_minutes(62.05));
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    {
        const std::chrono::seconds d = picker.chrono_duration<int, std::ratio<1> >();
        BOOST_TEST(d == std::chrono::seconds(time_1_2_3));
    }
    {
        const std::chrono::milliseconds d = picker.chrono_duration<int, std::milli >();
        BOOST_TEST(d == std::chrono::milliseconds(time_1_2_3 * 1000));
    }
    {
        typedef std::chrono::duration< double, std::chrono::minutes::period > double_minutes;
        const double_minutes d =
            picker.chrono_duration<double_minutes::rep, double_minutes::period >();
        BOOST_TEST(d == double_minutes(62.05));
    }
#endif

    // Test 03:02:01

    picker.set_time(3, 2, 1);
    {
        short hours = 0, seconds = 0, minutes = 0;
        picker.get_time(&hours, &seconds, &minutes);
        BOOST_TEST_EQ(hours, 3);
        BOOST_TEST_EQ(seconds, 2);
        BOOST_TEST_EQ(minutes, 1);
    }

    // Test std::tm

    {
        std::tm t = { 0 };
        t.tm_hour = 16;
        t.tm_min = 47;
        t.tm_sec = 59;
        picker.set_tm(t);

        BOOST_TEST_EQ(picker.get_time_t(), ((16 * 60) + 47) * 60 + 59);

#ifdef BOOST_UI_USE_DATE_TIME
        BOOST_TEST_EQ(picker.posix_time_duration(), boost::posix_time::time_duration(16, 47, 59));
#endif

        t.tm_sec = 61;
        picker.set_tm(t);

#ifdef BOOST_UI_USE_DATE_TIME
        BOOST_TEST_EQ(picker.posix_time_duration(), boost::posix_time::time_duration(16, 48, 1));
#endif
    }
    {
        std::tm t = { 0 };
        t.tm_hour = 24;
        BOOST_TEST_THROWS(picker.set_tm(t), std::out_of_range);
    }
    {
        std::tm t = { 0 };
        t.tm_min = 60;
        BOOST_TEST_THROWS(picker.set_tm(t), std::out_of_range);
    }
    {
        std::tm t = { 0 };
        t.tm_sec = 62;
        BOOST_TEST_THROWS(picker.set_tm(t), std::out_of_range);
    }

#ifdef BOOST_UI_USE_DATE_TIME
    // Test boost::posix_time::time_duration

    picker.posix_time_duration(boost::posix_time::time_duration(14, 35, 55));
    BOOST_TEST_EQ(picker.posix_time_duration(), boost::posix_time::time_duration(14, 35, 55));

    picker.posix_time_duration(boost::posix_time::time_duration(22, 75, 77));
    BOOST_TEST_EQ(picker.posix_time_duration(), boost::posix_time::time_duration(23, 16, 17));

    BOOST_TEST_THROWS(picker.posix_time_duration(boost::posix_time::time_duration(25, 0, 0)), std::out_of_range);
#endif

#ifdef BOOST_UI_USE_CHRONO
    // Test boost::chrono::duration

    picker.chrono_duration(boost::chrono::seconds(59));
    BOOST_TEST_EQ(picker.get_time_t(), 59);

    picker.chrono_duration(boost::chrono::seconds(71));
    BOOST_TEST_EQ(picker.get_time_t(), 71);

    picker.chrono_duration(boost::chrono::seconds(time_1_2_3));
    BOOST_TEST_EQ(picker.get_time_t(), time_1_2_3);

    picker.chrono_duration(boost::chrono::minutes(82));
    BOOST_TEST_EQ(picker.get_time_t(), 82 * 60);

    picker.chrono_duration(boost::chrono::duration<double, boost::chrono::minutes::period>(93.5));
    BOOST_TEST_EQ(picker.get_time_t(), 93 * 60 + 30);
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    // Test std::chrono::duration

    picker.chrono_duration(std::chrono::seconds(59));
    BOOST_TEST_EQ(picker.get_time_t(), 59);

    picker.chrono_duration(std::chrono::seconds(71));
    BOOST_TEST_EQ(picker.get_time_t(), 71);

    picker.chrono_duration(std::chrono::seconds(time_1_2_3));
    BOOST_TEST_EQ(picker.get_time_t(), time_1_2_3);

    picker.chrono_duration(std::chrono::minutes(82));
    BOOST_TEST_EQ(picker.get_time_t(), 82 * 60);

    picker.chrono_duration(std::chrono::duration<double, std::chrono::minutes::period>(93.5));
    BOOST_TEST_EQ(picker.get_time_t(), 93 * 60 + 30);
#endif
}

int ui_main()
{
    ui::dialog dlg("Title");

    test_date_picker(dlg);
    test_time_picker(dlg);

    //dlg.show_modal();

    return boost::report_errors();
}

int cpp_main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
