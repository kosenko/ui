// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file color_io.hpp Color I/O operations

#ifndef BOOST_UI_COLOR_IO_HPP
#define BOOST_UI_COLOR_IO_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/color.hpp>

#include <ostream>

namespace boost {
namespace ui    {

///@{ @brief Writes color into the stream
///   @relatesalso boost::ui::color

inline std::ostream& operator<<(std::ostream& s, const boost::ui::color& c)
{
    return s << "rgba"
        << '(' << static_cast<int>(c.red255())
        << ',' << static_cast<int>(c.green255())
        << ',' << static_cast<int>(c.blue255())
        << ',' << static_cast<int>(c.alpha255())
        << ')';
}

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COLOR_IO_HPP
