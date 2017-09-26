// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file event_loop.hpp Event loop class

#ifndef BOOST_UI_EVENT_LOOP_HPP
#define BOOST_UI_EVENT_LOOP_HPP

#include <boost/ui/config.hpp>

#include <boost/noncopyable.hpp>

namespace boost  {
namespace ui     {

/// @brief Event loop class
/// @see <a href="http://en.wikipedia.org/wiki/Event_loop">Event loop (Wikipedia)</a>
/// @ingroup event

class BOOST_UI_DECL event_loop : private boost::noncopyable
{
public:
    event_loop() : m_loop(NULL) {}

    /// Returns true only if event loop is running
    bool is_running() const;

    /// Start the event loop
    void run();

    /// Exit from the event loop
    void exit();

private:
    class native_impl;
    native_impl* m_loop;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_EVENT_LOOP_HPP
