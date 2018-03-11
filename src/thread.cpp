// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/thread.hpp>

#include <wx/app.h>

namespace boost  {
namespace ui     {
namespace detail {

void call_async(const boost::function<void()>& fn)
{
#ifdef wxHAS_CALL_AFTER
    wxAppConsole* app = wxApp::GetInstance();
    if ( app )
    {
        app->CallAfter(fn);
        return;
    }
#endif

    wxFAIL;
    fn();
}

} // namespace detail
} // namespace ui
} // namespace boost
