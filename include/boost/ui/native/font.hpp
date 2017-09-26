// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_FONT_HPP
#define BOOST_UI_NATIVE_FONT_HPP

class wxFont;

#include <boost/ui/font.hpp>

namespace boost  {
namespace ui     {
namespace native {

wxFont from_font(ui::font& f);
const wxFont from_font(const ui::font& f);
ui::font to_font(const wxFont& f);

} // namespace native
} // namespace ui
} // namespace boost

#endif // BOOST_UI_NATIVE_FONT_HPP
