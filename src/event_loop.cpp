// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/event_loop.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/evtloop.h>

namespace boost {
namespace ui    {

class event_loop::native_impl : public wxEventLoop, private detail::memcheck
{
public:
};

bool event_loop::is_running() const
{
    if ( !m_loop )
        return false;

    return m_loop->IsRunning();
}

void event_loop::run()
{
    wxCHECK_RET(!m_loop, "Event loop already runs");

    boost::scoped_ptr<native_impl> loop(m_loop = new event_loop::native_impl);
    m_loop->Run();
    m_loop = NULL;
}

void event_loop::exit()
{
    wxCHECK_RET(m_loop, "Event loop don't run");

    m_loop->Exit();
}

} // namespace ui
} // namespace boost
