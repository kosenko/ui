// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file string_io.hpp String I/O operations

#ifndef BOOST_UI_STRING_IO_HPP
#define BOOST_UI_STRING_IO_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/string.hpp>

#include <ostream>
#include <istream>

namespace boost {
namespace ui    {

///@{ @brief Writes string into the stream
///   @relatesalso boost::ui::uistring

#ifndef BOOST_UI_NO_STRING_DESTRUCTIVE
template <class Traits>
std::basic_ostream<char, Traits>&
operator<<(std::basic_ostream<char, Traits>& os, const uistring& str)
{
    return os << str.string();
}
#endif

template <class Traits>
std::basic_ostream<wchar_t, Traits>&
operator<<(std::basic_ostream<wchar_t, Traits>& os, const uistring& str)
{
    return os << str.wstring();
}

#ifndef BOOST_NO_CXX11_CHAR16_T
template <class Traits>
std::basic_ostream<char16_t, Traits>&
operator<<(std::basic_ostream<char16_t, Traits>& os, const uistring& str)
{
    return os << str.u16string();
}
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
template <class Traits>
std::basic_ostream<char32_t, Traits>&
operator<<(std::basic_ostream<char32_t, Traits>& os, const uistring& str)
{
    return os << str.u32string();
}
#endif

///@}

///@{ @brief Reads string from the stream
///   @relatesalso boost::ui::uistring
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
template <class Traits>
std::basic_istream<char, Traits>&
operator>>(std::basic_istream<char, Traits>& is, ui::uistring& str)
{
    std::string temp;
    is >> temp;
    str = temp;
    return is;
}
#endif

template <class Traits>
std::basic_istream<wchar_t, Traits>&
operator>>(std::basic_istream<wchar_t, Traits>& is, ui::uistring& str)
{
    std::wstring temp;
    is >> temp;
    str = temp;
    return is;
}

#ifndef BOOST_NO_CXX11_CHAR16_T
template <class Traits>
std::basic_istream<char16_t, Traits>&
operator>>(std::basic_istream<char16_t, Traits>& is, ui::uistring& str)
{
    std::u16string temp;
    is >> temp;
    str = temp;
    return is;
}
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
template <class Traits>
std::basic_istream<char32_t, Traits>&
operator>>(std::basic_istream<char32_t, Traits>& is, ui::uistring& str)
{
    std::u32string temp;
    is >> temp;
    str = temp;
    return is;
}
#endif

///@}

} // namespace ui
} // namespace boost

namespace std {

///@{ @brief Reads characters from the stream into the string
///   @relatesalso boost::ui::uistring
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
template <class Traits>
std::basic_istream<char, Traits>&
getline(std::basic_istream<char, Traits>& is, boost::ui::uistring& str, char ch = '\n')
{
    std::string temp;
    std::getline(is, temp, ch);
    str = temp;
    return is;
}
#endif

template <class Traits>
std::basic_istream<wchar_t, Traits>&
getline(std::basic_istream<wchar_t, Traits>& is, boost::ui::uistring& str, wchar_t ch = L'\n')
{
    std::wstring temp;
    std::getline(is, temp, ch);
    str = temp;
    return is;
}

#ifndef BOOST_NO_CXX11_CHAR16_T
template <class Traits>
std::basic_istream<char16_t, Traits>&
getline(std::basic_istream<char16_t, Traits>& is, boost::ui::uistring& str, char16_t ch = u'\n')
{
    std::u16string temp;
    std::getline(is, temp, ch);
    str = temp;
    return is;
}
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
template <class Traits>
std::basic_istream<char32_t, Traits>&
getline(std::basic_istream<char32_t, Traits>& is, boost::ui::uistring& str, char32_t ch = U'\n')
{
    std::u32string temp;
    std::getline(is, temp, ch);
    str = temp;
    return is;
}
#endif

///@}

} // namespace std

#endif // BOOST_UI_STRING_IO_HPP
