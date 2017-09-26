// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_CHRONO)
#include <chrono>
namespace chrono_ns = std::chrono;
#else
#define BOOST_UI_USE_CHRONO
#include <boost/chrono.hpp>
#include <boost/chrono/time_point.hpp>
namespace chrono_ns = boost::chrono;
#endif

#include <boost/ui.hpp>
#include <boost/bind.hpp>

#include <queue>
#include <sstream>

namespace ui = boost::ui;

struct time_point
{
    chrono_ns::time_point<chrono_ns::system_clock> system;
    chrono_ns::time_point<chrono_ns::steady_clock> steady;
    chrono_ns::time_point<chrono_ns::high_resolution_clock> high_resolution;

    static time_point now()
    {
        time_point tp;
        tp.system = chrono_ns::system_clock::now();
        tp.steady = chrono_ns::steady_clock::now();
        tp.high_resolution = chrono_ns::high_resolution_clock::now();
        return tp;
    }
};

class chrono_dialog : public ui::dialog
{
    typedef chrono_dialog this_type;

public:
    chrono_dialog();

private:
    void on_start();
    void on_clear();
    void on_timeout();

    ui::listbox m_results_listbox;
    std::queue<time_point> m_time_points;
};

chrono_dialog::chrono_dialog() : ui::dialog(
#if !defined(BOOST_NO_CXX11_HDR_CHRONO)
    "C++11 "
#else
    "Boost."
#endif
    "Chrono + Boost.UI example")
{
    ui::vbox(*this)
        << ( ui::hbox()
            << ui::button(*this, "&Start")
                .on_press(&this_type::on_start, this)
            << ui::button(*this, "&Clear results")
                .on_press(&this_type::on_clear, this)
           )
        << m_results_listbox.create(*this)
            .tooltip("Timeout precision")
            .layout().stretch().justify()
        ;

    resize(1000, 500);
}

static chrono_ns::milliseconds g_duration =
    chrono_ns::milliseconds(1000);

void chrono_dialog::on_start()
{
    ui::on_timeout(g_duration,
                   boost::bind(&this_type::on_timeout, this));
    m_time_points.push(time_point::now());
}

void chrono_dialog::on_clear()
{
    m_results_listbox.clear();
}

void chrono_dialog::on_timeout()
{
    const time_point now = time_point::now();
    const chrono_ns::duration<double> elapsed_system =
        now.system - m_time_points.front().system;
    const chrono_ns::duration<double> elapsed_steady =
        now.steady - m_time_points.front().steady;
    const chrono_ns::duration<double> elapsed_high_resolution =
        now.high_resolution - m_time_points.front().high_resolution;
    m_time_points.pop();

    std::ostringstream ss;
    ss << "system: " << (elapsed_system - g_duration).count() << " (";
    ss << (elapsed_system - g_duration) / g_duration * 100 << "%)";
    ss << ", steady: " << (elapsed_steady - g_duration).count() << " (";
    ss << (elapsed_steady - g_duration) / g_duration * 100 << "%)";
    ss << ", high resolution: " << (elapsed_high_resolution - g_duration).count() << " (";
    ss << (elapsed_high_resolution - g_duration) / g_duration * 100 << "%)";

    m_results_listbox.push_back(ss.str());
}

int ui_main()
{
    chrono_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
