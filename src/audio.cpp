// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/audio.hpp>

#include <wx/utils.h>

namespace boost {
namespace ui    {

void beep()
{
    wxBell();
}

} // namespace ui
} // namespace boost
