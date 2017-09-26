// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_COLOR_HPP
#define BOOST_UI_NATIVE_COLOR_HPP

#include <wx/colour.h>

namespace boost  {
namespace ui     {
namespace native {

inline wxColor from_color(const color& c)
{
    return wxColor(c.red255(), c.green255(), c.blue255(), c.alpha255());
}

} // namespace native
} // namespace ui
} // namespace boost

#endif // BOOST_UI_NATIVE_COLOR_HPP
