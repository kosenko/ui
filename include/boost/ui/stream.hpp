// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file stream.hpp Stream class and manipulators

#ifndef BOOST_UI_STREAM_HPP
#define BOOST_UI_STREAM_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <sstream>

#include <boost/ui/string.hpp>

namespace boost {
namespace ui    {

/// @brief Output string stream that collects data for UI
/// @ingroup helper

class uiostringstream
{
public:
    /// Creates empty stream
    uiostringstream() {}

    /// @brief Creates stream and adds @a value to it
    uiostringstream(const uistring& value) : m_buffer(value) {}

    /// @brief Process stream manipulator
    uiostringstream& operator<<(boost::ui::uiostringstream& (*func)(boost::ui::uiostringstream&))
    {
        return func(*this);
    }

    ///@{ @brief Inserts data into stream
    uiostringstream& operator<<(short value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(unsigned short value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(int value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(unsigned int value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(long value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(unsigned long value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(long long value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(unsigned long long value)
    {
        m_buffer += to_uistring(value);
        return *this;
    }
    uiostringstream& operator<<(float value);
    uiostringstream& operator<<(double value);
    uiostringstream& operator<<(bool value)
    {
        m_buffer += ascii(value ? "1" : "0");
        return *this;
    }
    uiostringstream& operator<<(char value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const char* value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const std::string& value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(wchar_t value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const wchar_t* value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const std::wstring& value)
    {
        m_buffer += value;
        return *this;
    }
#ifndef BOOST_NO_CXX11_CHAR16_T
    uiostringstream& operator<<(char16_t value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const char16_t* value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const std::u16string& value)
    {
        m_buffer += value;
        return *this;
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    uiostringstream& operator<<(char32_t value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const char32_t* value)
    {
        m_buffer += value;
        return *this;
    }
    uiostringstream& operator<<(const std::u32string& value)
    {
        m_buffer += value;
        return *this;
    }
#endif
    template <class T>
    uiostringstream& operator<<(const T& value)
    {
        std::wostringstream ss;
        ss << value;
        m_buffer += ss.str();
        return *this;
    }
    ///@}

    /// @brief Exchanges contents of the streams
    void swap(uiostringstream& other) { m_buffer.swap(other.m_buffer); }

    /// @brief Returns collected data as a string
    uistring str() const { return m_buffer; }

    /// @brief Resets built-in collected data with @a value
    void str(const uistring& value) { m_buffer = value; }

private:
    uistring m_buffer;
};

} // namespace ui
} // namespace boost

namespace std {

/// @brief Specializes the std::swap algorithm
/// @relatesalso boost::ui::uiostringstream
inline void swap(boost::ui::uiostringstream& a, boost::ui::uiostringstream& b) { a.swap(b); }

/// @brief Manipulator that inserts newline character into stream
/// @relatesalso boost::ui::uiostringstream
inline boost::ui::uiostringstream& endl(boost::ui::uiostringstream& os)
{
    return os << '\n';
}

} // namespace std

#endif // BOOST_UI_STREAM_HPP
