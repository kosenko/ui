// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file message.hpp Display message file

#ifndef BOOST_UI_MESSAGE_HPP
#define BOOST_UI_MESSAGE_HPP

#ifdef DOXYGEN
#define BOOST_UI_USE_FILESYSTEM
#endif

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/string.hpp>
#include <boost/ui/color.hpp>

#ifdef BOOST_UI_USE_FILESYSTEM
#include <boost/filesystem.hpp>
#endif

namespace boost {
namespace ui    {

/// @brief Display information as an non intrusive notification
/// @ingroup notify
BOOST_UI_DECL
void info_notify(const uistring& message,
                 const uistring& title = ascii("Information"));

/// @brief Display warning as an non intrusive notification
/// @ingroup notify
BOOST_UI_DECL
void warning_notify(const uistring& message,
                    const uistring& title = ascii("Warning"));

/// @brief Display error as an non intrusive notification
/// @ingroup notify
BOOST_UI_DECL
void error_notify(const uistring& message,
                  const uistring& title = ascii("Error"));


/// @brief Display information in application-modal dialog
/// @ingroup alert
BOOST_UI_DECL
void info_dialog(const uistring& message,
                 const uistring& title = ascii("Information"));

/// @brief Display warning in application-modal dialog
/// @ingroup alert
BOOST_UI_DECL
void warning_dialog(const uistring& message,
                    const uistring& title = ascii("Warning"));

/// @brief Display error in application-modal dialog
/// @ingroup alert
BOOST_UI_DECL
void error_dialog(const uistring& message,
                  const uistring& title = ascii("Error"));

/// @brief Request user confirmation using application-modal dialog
/// @see <a href="http://en.wikipedia.org/wiki/Confirmation_dialog_box">Confirmation dialog box (Wikipedia)</a>
/// @ingroup alert
BOOST_UI_DECL
bool confirm(const uistring& message,
             const uistring& title = ascii("Confirmation"));

/// @brief Request user answer using application-modal dialog
/// @ingroup alert
BOOST_UI_DECL
bool question(const uistring& message,
              const uistring& title = ascii("Question"));


///@{ @brief Request user value using application-modal dialog
/// @ingroup prompt
BOOST_UI_DECL
bool prompt(const uistring& message, const uistring& title, std::wstring& value);
BOOST_UI_DECL
bool prompt(const uistring& message, const uistring& title, uistring& value);
///@}

///@{ @brief Request user password using application-modal dialog
/// @ingroup prompt
BOOST_UI_DECL
bool prompt_password(const uistring& message, const uistring& title, std::wstring& value);
BOOST_UI_DECL
bool prompt_password(const uistring& message, const uistring& title, uistring& value);
///@}

///@{ @brief Request user filename using application-modal dialog
/// @see BOOST_UI_USE_FILESYSTEM
/// @ingroup prompt
BOOST_UI_DECL
bool prompt_filename(const uistring& title, std::wstring& value);
BOOST_UI_DECL
bool prompt_filename(const uistring& title, uistring& value);
#ifdef BOOST_UI_USE_FILESYSTEM
inline bool prompt_filename(const uistring& title, boost::filesystem::path& value)
{
    uistring str = value.wstring();
    if ( !prompt_filename(title, str) )
        return false;

    value = str.wstring();
    return true;
}
#endif
///@}

///@{ @brief Request user directory using application-modal dialog
/// @see BOOST_UI_USE_FILESYSTEM
/// @ingroup prompt
BOOST_UI_DECL
bool prompt_directory(const uistring& title, std::wstring& value);
BOOST_UI_DECL
bool prompt_directory(const uistring& title, uistring& value);
#ifdef BOOST_UI_USE_FILESYSTEM
inline bool prompt_directory(const uistring& title, boost::filesystem::path& value)
{
    uistring str = value.wstring();
    if ( !prompt_directory(title, str) )
        return false;

    value = str.wstring();
    return true;
}
#endif
///@}

///@{ @brief Request color using application-modal dialog
/// @ingroup prompt
BOOST_UI_DECL
bool prompt_color(const uistring& title, color& value);
///@}

} // namespace ui
} // namespace boost

#endif // BOOST_UI_MESSAGE_HPP
