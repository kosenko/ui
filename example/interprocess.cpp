// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Provide data exchange between processes using Boost.Interprocess.

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

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <sstream>

namespace ui = boost::ui;

class interprocess_dialog : public ui::dialog
{
    typedef interprocess_dialog this_type;

public:
    interprocess_dialog();

private:
    void on_lock();
    void on_unlock();
    void on_timeout();
    boost::interprocess::named_mutex m_mutex;
    ui::label m_lock_label;

    void on_send();
    void on_recieve();
    boost::interprocess::message_queue m_mq;
};

#define MAX_MSG_SIZE 30
static const char g_mutex_name[] = "Boost.Interprocess.Mutex";
static const char g_message_queue_name[] = "Boost.Interprocess.MessageQueue";

interprocess_dialog::interprocess_dialog() :
    ui::dialog("Boost.Interprocess + Boost.UI example"),
    m_mutex(boost::interprocess::open_or_create, g_mutex_name),
    m_mq(boost::interprocess::open_or_create, g_message_queue_name,
         10, MAX_MSG_SIZE)
{
    ui::vbox(*this)
        << ( ui::hbox()
            << ui::label(*this, "Mutex:")
                .tooltip(g_mutex_name)
            << ui::button(*this, "&Lock")
                .on_press(&this_type::on_lock, this)
            << ui::button(*this, "&Unlock")
                .on_press(&this_type::on_unlock, this)
            << m_lock_label.create(*this)
           )
        << ( ui::hbox()
            << ui::label(*this, "Message queue:")
                .tooltip(g_message_queue_name)
            << ui::button(*this, "&Send current date and time")
                .on_press(&this_type::on_send, this)
            << ui::button(*this, "&Recieve all messages")
                .on_press(&this_type::on_recieve, this)
           )
        ;

    on_timeout();
}

void interprocess_dialog::on_lock()
{
    if ( !m_mutex.try_lock() )
        ui::error_dlg("Mutex is already locked");
}

void interprocess_dialog::on_unlock()
{
    m_mutex.unlock();
}

void interprocess_dialog::on_timeout()
{
    const bool was_locked = !m_mutex.try_lock();
    if ( !was_locked )
        m_mutex.unlock();

    m_lock_label.text(was_locked ? "Locked" : "Unlocked");

    ui::on_timeout(chrono_ns::milliseconds(100),
                   boost::bind(&this_type::on_timeout, this));
}

void interprocess_dialog::on_send()
{
    char buffer[MAX_MSG_SIZE];
    strncpy(buffer, boost::posix_time::to_iso_extended_string(
            boost::posix_time::second_clock::local_time()).c_str(), MAX_MSG_SIZE);
    m_mq.send(&buffer, sizeof buffer, 0);
}

void interprocess_dialog::on_recieve()
{
    std::ostringstream ss;
    int i = 0;

    for ( ;; i++ )
    {
        char buffer[MAX_MSG_SIZE];
        boost::interprocess::message_queue::size_type recieved_size;
        unsigned priority;
        if ( !m_mq.try_receive(&buffer, sizeof buffer, recieved_size, priority) )
            break;
        else
            ss << i << ") \"" << buffer << "\"" << std::endl;
    }

    if ( i == 0 )
        ss << "There is no new messages";

    ui::info_dlg(ss.str(), "Messages");
}

int ui_main()
{
    interprocess_dialog().show_modal();

    boost::interprocess::named_mutex::remove(g_mutex_name);
    boost::interprocess::message_queue::remove(g_message_queue_name);

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(argc, argv, &ui_main);
}
