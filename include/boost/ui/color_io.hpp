// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file color_io.hpp Color I/O operations

#ifndef BOOST_UI_COLOR_IO_HPP
#define BOOST_UI_COLOR_IO_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/color.hpp>

#include <ostream>

namespace boost {
namespace ui    {

///@{ @brief Writes color into the stream
///   @relatesalso boost::ui::color

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const boost::ui::color& c)
{
    const bool is_transparent = c.alpha255() != 255;
    os << 'r' << 'g' << 'b';
    if ( is_transparent )
        os << 'a';
    os << '(' << static_cast<int>(c.red255());
    os << ',' << static_cast<int>(c.green255());
    os << ',' << static_cast<int>(c.blue255());
    if ( is_transparent )
        os << ',' << static_cast<int>(c.alpha255());
    os << ')';
    return os;
}

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COLOR_IO_HPP
