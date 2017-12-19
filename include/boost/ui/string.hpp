// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file string.hpp String class and operations

#ifndef BOOST_UI_STRING_HPP
#define BOOST_UI_STRING_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <string>

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#ifndef BOOST_UI_NO_STD_HASH
#include <functional>
#endif

#ifdef DOXYGEN

/// @brief Disables potentially destructive string operations
/// with conversion from uistring to ASCII
/// @relatesalso boost::ui::uistring
/// @ingroup helper

#define BOOST_UI_NO_STRING_DESTRUCTIVE

/// @brief Disables implicit conversion from ASCII to uistring
/// @relatesalso boost::ui::uistring
/// @ingroup helper
#define BOOST_UI_NO_CAST_FROM_ASCII

#endif // DOXYGEN

namespace boost {
namespace ui    {

/// @brief Helper class to convert string between UI and application logic only
/// @ingroup helper

class BOOST_UI_DECL uistring
{
public:
    /// Unsigned integral type
    typedef std::size_t size_type;

    uistring();

    ///@{ Constructs uistring from other uistring
    uistring(const uistring& other);
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    uistring(uistring&& other)
    {
        init();
        swap(other);
    }
#endif
    ///@}

#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    ///@{ Constructs uistring from narrow char* string using current locale encoding
    uistring(const char* str);
    uistring(const std::string& str);
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    uistring(std::initializer_list<char> list)
    {
        init();
        append(list);
    }
#endif
    ///@}
#endif

    ///@{ Constructs uistring from Unicode wide char string
    uistring(const wchar_t* str);
    uistring(const std::wstring& str);
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    uistring(std::initializer_list<wchar_t> list)
    {
        init();
        append(list);
    }
#endif
    ///@}

    ///@{ Constructs uistring from UTF-16 string
#ifndef BOOST_NO_CXX11_CHAR16_T
    uistring(const char16_t* str) { init(std::u16string(str)); }
    uistring(const std::u16string& str) { init(str); }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    uistring(std::initializer_list<char16_t> list)
    {
        init();
        append(list);
    }
#endif
#endif
    ///@}

    ///@{ Constructs uistring from UTF-32 string
#ifndef BOOST_NO_CXX11_CHAR32_T
    uistring(const char32_t* str) { init(std::u32string(str)); }
    uistring(const std::u32string& str) { init(str); }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    uistring(std::initializer_list<char32_t> list)
    {
        init();
        append(list);
    }
#endif
#endif
    ///@}

    ~uistring();

    ///@{ Assigns other string to this string
    uistring& assign(const uistring& other);
    uistring& operator=(const uistring& other) { return assign(other); }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    uistring& assign(uistring&& other)
    {
        swap(other);
        return *this;
    }
    uistring& operator=(uistring&& other)
    {
        // return assign(other); // not works
        swap(other);
        return *this;
    }
#endif
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    uistring& assign(std::initializer_list<char> list)
    {
        clear();
        return append(list);
    }
    uistring& operator=(std::initializer_list<char> list) { return assign(list); }
#endif
    uistring& assign(std::initializer_list<wchar_t> list)
    {
        clear();
        return append(list);
    }
    uistring& operator=(std::initializer_list<wchar_t> list) { return assign(list); }
#endif
    ///@}

    ///@{ Appends characters to the end of string
    uistring& append(const uistring& str);
    uistring& operator+=(const uistring& str) { return append(str); }
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    uistring& append(size_type count, char ch);
#endif
    uistring& append(size_type count, wchar_t ch);
#ifndef BOOST_NO_CXX11_CHAR16_T
    uistring& append(size_type count, char16_t ch)
        { return append(count, static_cast<wchar_t>(ch)); }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    uistring& append(size_type count, char32_t ch)
        { return append(count, static_cast<wchar_t>(ch)); }
#endif
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    uistring& append(std::initializer_list<char> list)
    {
        for ( std::initializer_list<char>::const_iterator i = list.begin();
             i != list.end(); ++i )
             push_back(*i);

        return *this;
    }
    uistring& operator+=(std::initializer_list<char> list) { return append(list); }
#endif
    uistring& append(std::initializer_list<wchar_t> list)
    {
        for ( std::initializer_list<wchar_t>::const_iterator i = list.begin();
             i != list.end(); ++i )
             push_back(*i);

        return *this;
    }
    uistring& operator+=(std::initializer_list<wchar_t> list) { return append(list); }
#ifndef BOOST_NO_CXX11_CHAR16_T
    uistring& append(std::initializer_list<char16_t> list)
    {
        for ( std::initializer_list<char16_t>::const_iterator i = list.begin();
             i != list.end(); ++i )
             push_back(*i);

        return *this;
    }
    uistring& operator+=(std::initializer_list<char16_t> list) { return append(list); }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    uistring& append(std::initializer_list<char32_t> list)
    {
        for ( std::initializer_list<char32_t>::const_iterator i = list.begin();
             i != list.end(); ++i )
             push_back(*i);

        return *this;
    }
    uistring& operator+=(std::initializer_list<char32_t> list) { return append(list); }
#endif
#endif
    ///@}

    ///@{ Appends character to the end of string
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    void push_back(char ch);
    uistring& operator+=(char ch) { push_back(ch); return *this; }
#endif
    void push_back(wchar_t ch);
    uistring& operator+=(wchar_t ch) { push_back(ch); return *this; }
#ifndef BOOST_NO_CXX11_CHAR16_T
    void push_back(char16_t ch) { push_back(static_cast<wchar_t>(ch)); }
    uistring& operator+=(char16_t ch) { push_back(ch); return *this; }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    void push_back(char32_t ch) { push_back(static_cast<wchar_t>(ch)); }
    uistring& operator+=(char32_t ch) { push_back(ch); return *this; }
#endif
    ///@}

    ///@{ Lexicographically compares two strings
    int compare(const uistring& other) const BOOST_NOEXCEPT;
    bool operator==(const uistring& other) const BOOST_NOEXCEPT
        { return compare(other) == 0; }
    bool operator!=(const uistring& other) const BOOST_NOEXCEPT
        { return compare(other) != 0; }
    bool operator<(const uistring& other)  const BOOST_NOEXCEPT
        { return compare(other) < 0; }
    bool operator<=(const uistring& other) const BOOST_NOEXCEPT
        { return compare(other) <= 0; }
    bool operator>(const uistring& other)  const BOOST_NOEXCEPT
        { return compare(other) > 0; }
    bool operator>=(const uistring& other) const BOOST_NOEXCEPT
        { return compare(other) >= 0; }
    ///@}

    /// Exchanges the contents of strings
    void swap(const uistring& other);

    /// Checks whether the string is empty
    bool empty() const BOOST_NOEXCEPT;

    /// Clears the contents
    void clear() BOOST_NOEXCEPT;

    /// Requests the removal of unused capacity
    void shrink_to_fit();

    /// @brief Returns UTF-8/16/32 encoded string
    /// Returns UTF-8 encoded string if charT is char,
    /// returns UTF-16 encoded string if charT is char16_t,
    /// returns UTF-32 encoded string if charT is char32_t,
    /// returns std::wstring if charT is wchar_t
    template <class charT>
    std::basic_string<charT> utf() const;

    /// @brief Returns std::basic_string<charT>
    template <class charT>
    std::basic_string<charT> basic_string() const;

    /// Returns UTF-8 encoded string
    std::string u8string() const;

#ifndef BOOST_UI_NO_STRING_DESTRUCTIVE
    /// @brief Returns 7-bit ASCII encoded string
    /// Replaces 8-bit items with underscore symbol (_)
    std::string asciistring() const;

    /// Returns std::string using current locale encoding
    std::string string() const;
#endif

    /// Returns Unicode wide std::wstring
    std::wstring wstring() const;

#ifndef BOOST_NO_CXX11_CHAR16_T
    ///@brief Returns UTF-16 std::u16string
    std::u16string u16string() const
        { return xstring<std::u16string>(); }
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
    ///@{ Returns UTF-32 std::u32string
    std::u32string u32string() const
        { return xstring<std::u32string>(); }
    ///@}
#endif

    /// Implementation-defined string type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying string handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    void init();
    void init(const std::wstring& str);

    static uistring make_from_utf8(const char* str);
    static uistring make_from_ascii(const char* str);

    template <class String>
    void init(const String& str)
    {
        std::wstring wstr;
        wstr.reserve(str.size());
        for ( typename String::const_iterator iter = str.begin();
                iter != str.end(); ++iter )
             wstr.push_back(static_cast<wchar_t>(*iter));
        init(wstr);
    }

    template <class String>
    String xstring() const
    {
        const std::wstring wstr = wstring();
        String result;
        result.reserve(wstr.size());
        for ( std::wstring::const_iterator iter = wstr.begin();
                iter != wstr.end(); ++iter )
             result.push_back(*iter);
        return result;
    }

    class impl;
    impl* m_impl;

#ifndef DOXYGEN
    friend class native_helper;
    friend uistring u8uistring(const char* str);
    friend uistring asciiuistring(const char* str);
#endif
};

/// @brief Returns UTF-8 encoded string
template <>
inline std::basic_string<char> uistring::utf() const { return u8string(); }

#ifndef BOOST_UI_NO_STRING_DESTRUCTIVE
/// @brief Returns std::string
template <>
inline std::string uistring::basic_string() const { return string(); }
#endif

/// @brief Returns std::wstring
template <>
inline std::basic_string<wchar_t> uistring::utf() const { return wstring(); }

/// @brief Returns std::wstring
template <>
inline std::wstring uistring::basic_string() const { return wstring(); }

#ifndef BOOST_NO_CXX11_CHAR16_T
/// @brief Returns UTF-16 encoded string
template <>
inline std::basic_string<char16_t> uistring::utf() const { return u16string(); }

/// @brief Returns std::u16string
template <>
inline std::u16string uistring::basic_string() const { return u16string(); }
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
/// @brief Returns UTF-32 encoded string
template <>
inline std::basic_string<char32_t> uistring::utf() const { return u32string(); }

/// @brief Returns std::u32string
template <>
inline std::u32string uistring::basic_string() const { return u32string(); }
#endif

///@{ @brief Constructs @ref uistring from UTF-8 encoded string
///   @relatesalso boost::ui::uistring
inline uistring u8uistring(const char* str) { return uistring::make_from_utf8(str); }
inline uistring u8uistring(const std::string& str) { return u8uistring(str.c_str()); }
inline uistring utf8(const char* str) { return u8uistring(str); }
inline uistring utf8(const std::string& str) { return u8uistring(str.c_str()); }
///@}

///@{ @brief Constructs @ref uistring from 7-bit ASCII encoded string
///   @relatesalso boost::ui::uistring
inline uistring asciiuistring(const char* str) { return uistring::make_from_ascii(str); }
inline uistring asciiuistring(const std::string& str) { return asciiuistring(str.c_str()); }
inline uistring ascii(const char* str) { return asciiuistring(str); }
inline uistring ascii(const std::string& str) { return asciiuistring(str.c_str()); }
///@}

///@{ @brief Concatenates two strings or the string and the character
///   @relatesalso boost::ui::uistring
inline uistring operator+(const uistring& lhs, const uistring& rhs)
{
    uistring result(lhs);
    result.append(rhs);
    return result;
}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
inline uistring operator+(uistring&& lhs, const uistring& rhs)
{
    return std::move(lhs.append(rhs));
}
inline uistring operator+(const uistring& lhs, uistring&& rhs)
{
    uistring result(lhs);
    result.append(std::move(rhs));
    rhs.clear(); // TODO: Remove
    return result;
}
inline uistring operator+(uistring&& lhs, uistring&& rhs)
{
    return std::move(lhs.append(rhs));
}
#endif

#ifndef BOOST_UI_NO_CAST_FROM_ASCII
inline uistring operator+(const uistring& lhs, char rhs)
{
    uistring result(lhs);
    result.push_back(rhs);
    return result;
}
inline uistring operator+(const uistring& lhs, const char* rhs)
{
    uistring result(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(char lhs, const uistring& rhs)
{
    uistring result;
    result.push_back(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(const char* lhs, const uistring& rhs)
{
    uistring result;
    result.append(lhs);
    result.append(rhs);
    return result;
}
#endif
inline uistring operator+(const uistring& lhs, wchar_t rhs)
{
    uistring result(lhs);
    result.push_back(rhs);
    return result;
}
inline uistring operator+(const uistring& lhs, const wchar_t* rhs)
{
    uistring result(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(wchar_t lhs, const uistring& rhs)
{
    uistring result;
    result.push_back(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(const wchar_t* lhs, const uistring& rhs)
{
    uistring result;
    result.append(lhs);
    result.append(rhs);
    return result;
}
#ifndef BOOST_NO_CXX11_CHAR16_T
inline uistring operator+(const uistring& lhs, char16_t rhs)
{
    uistring result(lhs);
    result.push_back(rhs);
    return result;
}
inline uistring operator+(const uistring& lhs, const char16_t* rhs)
{
    uistring result(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(char16_t lhs, const uistring& rhs)
{
    uistring result;
    result.push_back(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(const char16_t* lhs, const uistring& rhs)
{
    uistring result;
    result.append(lhs);
    result.append(rhs);
    return result;
}
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
inline uistring operator+(const uistring& lhs, char32_t rhs)
{
    uistring result(lhs);
    result.push_back(rhs);
    return result;
}
inline uistring operator+(const uistring& lhs, const char32_t* rhs)
{
    uistring result(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(char32_t lhs, const uistring& rhs)
{
    uistring result;
    result.push_back(lhs);
    result.append(rhs);
    return result;
}
inline uistring operator+(const char32_t* lhs, const uistring& rhs)
{
    uistring result;
    result.append(lhs);
    result.append(rhs);
    return result;
}
#endif

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
inline uistring operator+(uistring&& lhs, char rhs)
{
    return std::move(lhs.append(1, rhs));
}
inline uistring operator+(uistring&& lhs, const char* rhs)
{
    return std::move(lhs.append(rhs));
}
#endif
inline uistring operator+(uistring&& lhs, wchar_t rhs)
{
    return std::move(lhs.append(1, rhs));
}
inline uistring operator+(uistring&& lhs, const wchar_t* rhs)
{
    return std::move(lhs.append(rhs));
}
#ifndef BOOST_NO_CXX11_CHAR16_T
inline uistring operator+(uistring&& lhs, char16_t rhs)
{
    return std::move(lhs.append(1, rhs));
}
inline uistring operator+(uistring&& lhs, const char16_t* rhs)
{
    return std::move(lhs.append(rhs));
}
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
inline uistring operator+(uistring&& lhs, char32_t rhs)
{
    return std::move(lhs.append(1, rhs));
}
inline uistring operator+(uistring&& lhs, const char32_t* rhs)
{
    return std::move(lhs.append(rhs));
}
#endif
#endif // BOOST_NO_CXX11_RVALUE_REFERENCES

///@}

/// @brief Returns hash of @ref uistring for boost::hash
/// @relatesalso boost::ui::uistring
BOOST_UI_DECL std::size_t hash_value(const uistring& val);

} // namespace ui
} // namespace boost

/// Standard C++ namespace
namespace std {

/// @brief Specializes the std::swap algorithm
/// @relatesalso boost::ui::uistring
inline void swap(boost::ui::uistring& a, boost::ui::uistring& b) { a.swap(b); }

#ifndef BOOST_UI_NO_STD_HASH

/// @brief std::hash specialization for @ref boost::ui::uistring
template<>
struct hash<boost::ui::uistring>
    : public std::unary_function<boost::ui::uistring, std::size_t>
{
    /// @brief Calculates the hash of the @ref boost::ui::uistring
    std::size_t operator()(const boost::ui::uistring& key) const
    {
        return std::hash<std::wstring>()(key.wstring());
    }
};

#endif

} // namespace std

#endif // BOOST_UI_STRING_HPP
