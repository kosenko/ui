// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/log.hpp>
#include <boost/ui/native/string.hpp>

#include <wx/log.h>

namespace boost {
namespace ui    {

log_string::log_string(uistring& str)
    : m_string(str), m_spaces(true), m_quotes(true)
{
}

log_string& log_string::location(const char* file, int line, const char* fn)
{
    std::ostringstream ss;

    if ( file )
        ss << file;
    if ( line >= 0 )
        ss << '[' << line << ']';
    if ( fn )
        ss << ' ' << fn;

    ss << ":";

    m_string.append(ascii(ss.str()));

    return *this;
}

void log_string::append_space()
{
    if ( m_spaces && !m_string.empty() )
        m_string.append(wxS(" "));
}

#ifndef BOOST_UI_NO_CAST_FROM_ASCII

log_string& log_string::operator<<(char value)
{
    append_space();

    if ( m_quotes )
        m_string.push_back('\'');

    m_string.push_back(value);

    if ( m_quotes )
        m_string.push_back('\'');

    return *this;
}

log_string& log_string::operator<<(const std::string& value)
{
    if ( m_quotes || !value.empty() )
        append_space();

    if ( m_quotes )
        m_string.push_back('"');

    m_string.append(value);

    if ( m_quotes )
        m_string.push_back('"');

    return *this;
}

#endif

log_string& log_string::operator<<(wchar_t value)
{
    append_space();

    if ( m_quotes )
        m_string.push_back('\'');

    m_string.push_back(value);

    if ( m_quotes )
        m_string.push_back('\'');

    return *this;
}

log_string& log_string::operator<<(const std::wstring& value)
{
    if ( m_quotes || !value.empty() )
        append_space();

    if ( m_quotes )
        m_string.push_back('"');

    m_string.append(value);

    if ( m_quotes )
        m_string.push_back('"');

    return *this;
}

log_string& log_string::operator<<(const uistring& value)
{
    if ( m_quotes || !value.empty() )
        append_space();

    if ( m_quotes )
        m_string.push_back('"');

    m_string.append(value);

    if ( m_quotes )
        m_string.push_back('"');

    return *this;
}

log_string&  log_string::raw(const uistring& value)
{
    if ( m_quotes || !value.empty() )
        append_space();

    m_string.append(value);

    return *this;
}

log::~log()
{
    flush();
}

void log::flush()
{
    switch ( m_level )
    {
        case fatal_level:
            wxLogFatalError(wxS("%s"), native::from_uistring(m_string));
            break;
        case error_level:
            wxLogError(wxS("%s"), native::from_uistring(m_string));
            break;
        case warning_level:
            wxLogWarning(wxS("%s"), native::from_uistring(m_string));
            break;
        case info_level:
            wxLogMessage(wxS("%s"), native::from_uistring(m_string));
            break;
        case verbose_level:
            wxLogVerbose(wxS("%s"), native::from_uistring(m_string));
            break;
        default:
            wxFAIL_MSG(wxS("Unknown log level"));
        case debug_level:
            wxLogDebug(wxS("%s"), native::from_uistring(m_string));
            break;
        case trace_level:
            wxLogTrace(wxS("%s"), native::from_uistring(m_string));
            break;
    }
}

} // namespace ui
} // namespace boost
