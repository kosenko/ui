// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Example of Boost.Date_Time integration with date and time pickers.
// It provides information about selected date and time.

#define BOOST_UI_USE_DATE_TIME

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace ui = boost::ui;

class date_time_dialog : public ui::dialog
{
    typedef date_time_dialog this_type;

public:
    date_time_dialog();

private:
    void on_date_change();
    ui::date_picker m_date_picker;
    ui::label m_date_label;

    void on_time_change();
    ui::time_picker m_time_picker;
    ui::label m_time_label;
};

date_time_dialog::date_time_dialog()
    : ui::dialog("Boost.Date_Time + Boost.UI example")
{
    ui::hbox(*this)
        << ( ui::vbox()
            << m_date_label.create(*this).layout().stretch().justify()
            << m_date_picker.create(*this)
                .on_change(boost::bind(&this_type::on_date_change, this))
                .layout().justify()
           ).layout().stretch().justify()
        << ( ui::vbox()
            << m_time_label.create(*this).layout().stretch().justify()
            << m_time_picker.create(*this)
                .on_change(boost::bind(&this_type::on_time_change, this))
                .layout().justify()
           ).layout().stretch().justify()
        ;

    on_date_change();
    on_time_change();

    resize(600, 400);
}

void date_time_dialog::on_date_change()
{
    std::ostringstream ss;
    namespace gr = boost::gregorian;
    const gr::date d = m_date_picker.gregorian_date();
    ss << "Date: " << d;
    ss << "\nYear: " << d.year();
    ss << ", month: " << d.month()
       << " (" << d.month().as_number()
       << ", " << d.month().as_long_string();
    ss << "), day: " << d.day();
    ss << "\nDay of week: " << d.day_of_week()
       << " (" << d.day_of_week().as_number()
       << ", " << d.day_of_week().as_long_string() << ")";
    ss << "\nWeek number: " << d.week_number();
    ss << "\nDay of year: " << d.day_of_year();
    ss << "\nIs leap year: " << std::boolalpha <<
        gr::gregorian_calendar::is_leap_year(d.year());
    ss << "\nJulian Day number: " << d.julian_day();
    ss << "\nModified Julian Day number: " << d.modjulian_day();
    ss << "\nSimple string: " << gr::to_simple_string(d);
    ss << "\nISO string: " << gr::to_iso_string(d);
    ss << "\nISO extended string: " << gr::to_iso_extended_string(d);
    ss << "\nSQL string: " << gr::to_sql_string(d);
    ss << "\nDays since today: " << (d - gr::day_clock::local_day()).days();
    ss << "\nLast day of the month: " << d.end_of_month();
    ss << "\nLast Sunday of the month: " <<
        gr::last_day_of_the_week_in_month(gr::Sunday, d.month()).get_date(d.year());
    ss << "\nNext Saturday: " <<
        gr::first_day_of_the_week_after(gr::Saturday).get_date(d);
    // The Tuesday right after the first Monday in November
    ss << "\nUS Election Day: " <<
        gr::first_day_of_the_week_in_month(gr::Monday, gr::Nov).get_date(d.year())
        + gr::days(1);
    ss << "\nEpoch: " << gr::date(gr::gregorian_calendar::epoch());
    m_date_label.text(ss.str());
}

void date_time_dialog::on_time_change()
{
    std::ostringstream ss;
    const boost::posix_time::time_duration td = m_time_picker.posix_time_duration();
    ss << td;
    ss << "\nTotal seconds: " << td.total_seconds();
    ss << "\nSimple string: " << boost::posix_time::to_simple_string(td);
    ss << "\nISO string: " << boost::posix_time::to_iso_string(td);
    ss << "\nTicks per second: " << td.ticks_per_second();
    m_time_label.text(ss.str());
}

int ui_main()
{
    date_time_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
