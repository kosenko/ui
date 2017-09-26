// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file coord_io.hpp Coordinates I/O

#ifndef BOOST_UI_COORD_IO_HPP
#define BOOST_UI_COORD_IO_HPP

#include <boost/ui/config.hpp>
#include <ostream>
#include <sstream>

namespace boost {
namespace ui {

/// @brief Writes basic_size into basic_size stream.
/// @relatesalso boost::ui::basic_size
template <class T, class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const basic_size<T>& p)
{
    return os << '(' << p.width() << ',' << p.height() << ')';
}

/// @brief Writes basic_point into the stream.
/// @relatesalso boost::ui::basic_point
template <class T, class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const basic_point<T>& p)
{
    return os << '(' << p.x() << ',' << p.y() << ')';
}

/// @brief Writes basic_rect into the stream.
/// @relatesalso boost::ui::basic_rect
template <class T, class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const basic_rect<T>& r)
{
    return os << '(' << r.x() << ',' << r.y() << ',' << r.width() << ',' << r.height() << ')';
}

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COORD_IO_HPP
