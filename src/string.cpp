// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/string.hpp>
#include <boost/ui/string_io.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/functional/hash.hpp>

#include <wx/string.h>
#include <wx/log.h>

#include <stdio.h> // for snprintf()

namespace boost {
namespace ui    {

class uistring::impl : public wxString, private detail::memcheck
{
};

void uistring::init()
{
    m_impl = new impl;
}

uistring::uistring()
{
    init();
}

uistring::uistring(const uistring& other)
{
    init();
    *m_impl = *other.m_impl;
}

#ifndef BOOST_UI_NO_CAST_FROM_ASCII

uistring::uistring(const char* str)
{
    init();
    *static_cast<wxString*>(m_impl) = str;
}

uistring::uistring(const std::string& str)
{
    init();
    *static_cast<wxString*>(m_impl) = str;
}

#endif

uistring::uistring(const wchar_t* str)
{
    init();
    *static_cast<wxString*>(m_impl) = str;
}

uistring::uistring(const std::wstring& str)
{
    init();
    *static_cast<wxString*>(m_impl) = str;
}

void uistring::init(const std::wstring& str)
{
    init();
    *static_cast<wxString*>(m_impl) = str;
}

uistring::~uistring()
{
    delete m_impl;
}

uistring& uistring::assign(const uistring& other)
{
    m_impl->assign(*other.m_impl);
    return *this;
}

uistring& uistring::append(const uistring& str)
{
    m_impl->append(*str.m_impl);
    return *this;
}

#ifndef BOOST_UI_NO_CAST_FROM_ASCII

uistring& uistring::append(size_type count, char ch)
{
    m_impl->append(count, ch);
    return *this;
}

#endif

uistring& uistring::append(size_type count, wchar_t ch)
{
    m_impl->append(count, ch);
    return *this;
}

#ifndef BOOST_UI_NO_CAST_FROM_ASCII

void uistring::push_back(char ch)
{
    (*m_impl) += ch;
}

#endif

void uistring::push_back(wchar_t ch)
{
    (*m_impl) += ch;
}

int uistring::compare(const uistring& other) const BOOST_NOEXCEPT
{
    return m_impl->compare(*other.m_impl);
}

void uistring::swap(const uistring& other)
{
    m_impl->swap(*other.m_impl);
}

bool uistring::empty() const BOOST_NOEXCEPT
{
    return m_impl->empty();
}

void uistring::clear() BOOST_NOEXCEPT
{
    m_impl->clear();
}

void uistring::shrink_to_fit()
{
    m_impl->Shrink();
}

uistring uistring::make_from_utf8(const char* str)
{
    uistring result;
    *static_cast<wxString*>(result.m_impl) = wxString::FromUTF8(str);
    return result;
}

uistring uistring::make_from_ascii(const char* str)
{
    uistring result;
    *static_cast<wxString*>(result.m_impl) = wxString::FromAscii(str);
    return result;
}

std::string uistring::u8string() const
{
    return std::string(m_impl->ToUTF8());
}

#ifndef BOOST_UI_NO_STRING_DESTRUCTIVE

std::string uistring::asciistring() const
{
    return std::string(m_impl->ToAscii());
}

std::string uistring::string() const
{
    return std::string(m_impl->ToStdString());
}

#endif

std::wstring uistring::wstring() const
{
    return std::wstring(m_impl->ToStdWstring());
}

namespace {

template <class T>
uistring to_uistring_detail(T value, const char* format)
{
    char buffer[32];
#ifdef _MSC_VER
    _snprintf
#else
    snprintf
#endif
        (buffer, sizeof buffer / sizeof buffer[0], format, value);
    return ascii(buffer);
}

} // unnamed namespace

uistring to_uistring(int value)
{
    return to_uistring_detail(value, "%d");
}

uistring to_uistring(unsigned int value)
{
    return to_uistring_detail(value, "%u");
}

uistring to_uistring(long value)
{
    return to_uistring_detail(value, "%ld");
}

uistring to_uistring(unsigned long value)
{
    return to_uistring_detail(value, "%lu");
}

uistring to_uistring(long long value)
{
    return to_uistring_detail(value, "%lld");
}

uistring to_uistring(unsigned long long value)
{
    return to_uistring_detail(value, "%llu");
}

uistring to_uistring(float value)
{
    return to_uistring_detail(value, "%f");
}

uistring to_uistring(double value)
{
    return to_uistring_detail(value, "%f");
}

uistring to_uistring(long double value)
{
    return to_uistring_detail(value, "%Lf");
}

std::size_t hash_value(const uistring& value)
{
    return boost::hash<std::wstring>()(value.wstring());
}

class native_helper
{
public:
    static wxString from_uistring(const uistring& str)
    {
        return *str.m_impl;
    }

    static uistring to_uistring(const wxString& str)
    {
        uistring result;
        *static_cast<wxString*>(result.m_impl) = str;
        return result;
    }
};

namespace native {

wxString from_uistring(const uistring& str)
{
    return native_helper::from_uistring(str);
}

uistring to_uistring(const wxString& str)
{
    return native_helper::to_uistring(str);
}

wxArrayString from_vector_uistring(const std::vector<uistring>& arr)
{
    wxArrayString result;
    result.reserve(arr.size());
    for ( std::vector<uistring>::const_iterator iter = arr.begin();
          iter != arr.end(); ++iter )
        result.push_back(native::from_uistring(*iter));
    return result;
}

} // namespace native

} // namespace ui
} // namespace boost
