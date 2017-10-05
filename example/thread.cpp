// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Fill text box using multiple worker threads.

#include <boost/ui.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "to_string.hpp"

#if !defined(BOOST_NO_CXX11_HDR_THREAD)
#include <thread>
namespace thread_ns = std;
#else
#include <boost/thread.hpp>
namespace thread_ns = boost;
#endif

namespace ui = boost::ui;

class thread_dialog : public ui::dialog
{
    typedef thread_dialog this_type;

public:
    thread_dialog();

private:
    void on_start();
    void thread_entry(int thread_number, int repeats);
    void write(int thread_number, int repeats);

    ui::text_box m_output_widget;
    ui::string_box m_threads_count_widget;
    ui::string_box m_repeats_widget;
};

thread_dialog::thread_dialog() : ui::dialog(
#if !defined(BOOST_NO_CXX11_HDR_THREAD)
    "C++11 "
#else
    "Boost."
#endif
    "Thread + Boost.UI Example")
{
    ui::hbox(*this)
        << m_output_widget.create(*this)
            .tooltip("Output")
            .layout().justify().stretch()
        << ( ui::vbox().layout().justify()
            << ui::label(*this, "Threads count:")
                .layout().margin(1, 1, 0, 1)
            << m_threads_count_widget.create(*this, to_string(
                    100 * thread_ns::thread::hardware_concurrency() ))
                .layout().justify()
            << ui::label(*this, "Repeats:")
                .layout().margin(1, 1, 0, 1)
            << m_repeats_widget.create(*this, "10")
                .layout().justify()
            << ui::button(*this, "&Start threads")
                .on_press(&this_type::on_start, this)
                .layout().justify()
           )
        ;

    resize(600, 400);
}

void thread_dialog::on_start()
{
    const int threads_count = boost::lexical_cast<int>(m_threads_count_widget.text());
    const int repeats       = boost::lexical_cast<int>(m_repeats_widget.text());

    m_output_widget.clear();

    for ( int i = 0; i < threads_count; i++ )
    {
        thread_ns::thread t(&this_type::thread_entry, this, i, repeats);
        t.detach();
    }
}

void thread_dialog::thread_entry(int thread_number, int repeats)
{
    // Not thread safe
    // write(thread_number, repeats);

    // Thread safe
    ui::call_async(boost::bind(&this_type::write, this,
                                thread_number, repeats));
}

void thread_dialog::write(int thread_number, int repeats)
{
    for ( int r = 0; r < repeats; r++ )
    {
        m_output_widget.text(m_output_widget.text() +
            boost::lexical_cast<std::string>(thread_number) + "-" +
            boost::lexical_cast<std::string>(r) + " ");
    }
}

int ui_main()
{
    thread_dialog().show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
