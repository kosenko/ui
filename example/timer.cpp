// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Runs function with boost::ui::on_timeout() function with 1 second delay and
// checks timeout error using Boost.Timer.

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_CHRONO)
#include <chrono>
namespace chrono_ns = std::chrono;
#else
#define BOOST_UI_USE_CHRONO
#include <boost/chrono.hpp>
namespace chrono_ns = boost::chrono;
#endif

#include <boost/ui.hpp>
#include <boost/bind.hpp>

#include <boost/timer/timer.hpp>

#include <queue>
#include <sstream>
#include <iomanip>

namespace ui = boost::ui;

class timer_dialog : public ui::dialog
{
    typedef timer_dialog this_type;

public:
    timer_dialog();

private:
    void on_start();
    void on_clear();
    void on_timeout();

    ui::listbox m_results_listbox;
    std::queue<boost::timer::cpu_timer> m_timers;
};

timer_dialog::timer_dialog() : ui::dialog("Boost.Timer + Boost.UI example")
{
    ui::vbox(*this)
        << ( ui::hbox()
            << ui::button(*this, "&Start")
                .on_press(&this_type::on_start, this)
                .tooltip("Start timer with one second delay and show results")
            << ui::button(*this, "&Clear results")
                .on_press(&this_type::on_clear, this)
                .tooltip("Clear log")
           )
		<< ui::label(*this, "Timer precision results of 1 second delay:")
        << m_results_listbox.create(*this)
            .tooltip("Timeout precision")
            .layout().stretch().justify()
        ;

    resize(1000, 500);
}

void timer_dialog::on_start()
{
    m_timers.push(boost::timer::cpu_timer());
    ui::on_timeout(chrono_ns::milliseconds(1000),
                   boost::bind(&this_type::on_timeout, this));
    m_timers.back().start();
}

void timer_dialog::on_clear()
{
    m_results_listbox.clear();
}

void timer_dialog::on_timeout()
{
    const boost::timer::cpu_times times = m_timers.front().elapsed();
    m_timers.pop();

    std::ostringstream ss;
    ss  <<  times.wall - 1e9 << "ns ("
        << (times.wall - 1e9) / 1.e9 * 100 << "%) ";

    const std::string format = boost::timer::format(times, 9);
    ss << " (" << format.substr(0, format.find_first_of('\n')) << ")";

    m_results_listbox.push_back(ss.str());
}

int ui_main()
{
    timer_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
