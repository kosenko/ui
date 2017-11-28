// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file log.hpp Classes for logging

#ifndef BOOST_UI_LOG_HPP
#define BOOST_UI_LOG_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/string.hpp>

#include <sstream> // for std::ostringstream

namespace boost {
namespace ui    {

/// @brief Logging stream class with output into provided @ref uistring
/// @ingroup log

class BOOST_UI_DECL log_string
{
public:
    /// Constructs log using string for output
    log_string(uistring& str);

    /// Inserts white space delitimers between output values
    log_string& spaces(bool show = true) { m_spaces = show; return *this; }

    /// Adds quotes near string and character output values
    log_string& quotes(bool show = true) { m_quotes = show; return *this; }

    /// Logs caller location in the source code
    log_string& location(const char* file, int line = -1, const char* fn = NULL);

    ///@{ Logs value
#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    log_string& operator<<(char value);
    log_string& operator<<(const char* value)
        { return operator<<(std::string(value)); }
    log_string& operator<<(const std::string& value);
#endif
    log_string& operator<<(wchar_t value);
    log_string& operator<<(const wchar_t* value)
        { return operator<<(std::wstring(value)); }
    log_string& operator<<(const std::wstring& value);
    log_string& operator<<(const uistring& value);

#ifndef BOOST_UI_NO_CAST_FROM_ASCII
    template <class T>
    log_string& operator<<(const T& value)
    {
        std::ostringstream ss;
        ss << std::boolalpha << value;
        raw(ss.str());
        return *this;
    }
#endif
    ///@}

    /// Logs string without quotes
    log_string& raw(const uistring& value);

private:
    void append_space();

    uistring& m_string;
    bool m_spaces;
    bool m_quotes;
};

/// @brief Logging stream class
/// @ingroup log

class BOOST_UI_DECL log : public log_string
{
public:
    log() : log_string(m_string), m_level(debug_level) {}
    ~log();

    class fatal;
    class error;
    class warning;
    class info;
    class verbose;
    class debug;
    class trace;

protected:
#ifndef DOXYGEN
    enum level_values
    {
        fatal_level, error_level, warning_level, info_level,
        verbose_level, debug_level, trace_level
    };

    log(level_values level) : log_string(m_string), m_level(level) {}
#endif

private:
    void flush();

    uistring m_string;
    level_values m_level;
};

/// @brief Logs current file, line and function
/// @relates boost::ui::log
/// @ingroup log
#define BOOST_UI_LOG ::boost::ui::log().location(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION)

/// @brief Shows error and abort immediately
/// @ingroup log
class log::fatal : public log
{
public:
    fatal() : log(fatal_level) {}
};

/// @brief Shows error dialog in idle time
/// @ingroup log
class log::error : public log
{
public:
    error() : log(error_level) {}
};

/// @brief Shows warning dialog in idle time
/// @ingroup log
class log::warning : public log
{
public:
    warning() : log(warning_level) {}
};

/// @brief Shows information dialog in idle time
/// @ingroup log
class log::info : public log
{
public:
    info() : log(info_level) {}
};

/// @brief Shows verbose information if application was started with --verbose option
/// @ingroup log
class log::verbose : public log
{
public:
    verbose() : log(verbose_level) {}
};

/// @brief Shows information in debug log
/// @ingroup log
class log::debug : public log
{
public:
    debug() : log(debug_level) {}
};

/// @brief Shows information in debug log
/// @ingroup log
class log::trace : public log
{
public:
    trace() : log(trace_level) {}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LOG_HPP
