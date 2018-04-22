// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/message.hpp>
#include <boost/ui/native/string.hpp>

#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <wx/notifmsg.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>

namespace boost {
namespace ui    {

void info_notify(const uistring& message, const uistring& title)
{
#if wxUSE_NOTIFICATION_MESSAGE
    if ( !wxNotificationMessage(native::from_uistring(title),
                                native::from_uistring(message),
                                NULL, wxICON_INFORMATION).Show() )
#endif
        info_dialog(message, title);
}

void warning_notify(const uistring& message, const uistring& title)
{
#if wxUSE_NOTIFICATION_MESSAGE
    if ( !wxNotificationMessage(native::from_uistring(title),
                                native::from_uistring(message),
                                NULL, wxICON_WARNING).Show() )
#endif
        warning_dialog(message, title);
}

void error_notify(const uistring& message, const uistring& title)
{
#if wxUSE_NOTIFICATION_MESSAGE
    if ( !wxNotificationMessage(native::from_uistring(title),
                                native::from_uistring(message),
                                NULL, wxICON_ERROR).Show() )
#endif
        error_dialog(message, title);
}

void info_dialog(const uistring& message, const uistring& title)
{
#if wxUSE_MSGDLG
    wxMessageBox(native::from_uistring(message), native::from_uistring(title),
                 wxCLOSE | wxICON_INFORMATION | wxCENTER);
#endif
}

void warning_dialog(const uistring& message, const uistring& title)
{
#if wxUSE_MSGDLG
    wxMessageBox(native::from_uistring(message), native::from_uistring(title),
                 wxCLOSE | wxICON_WARNING | wxCENTER);
#endif
}

void error_dialog(const uistring& message, const uistring& title)
{
#if wxUSE_MSGDLG
    wxMessageBox(native::from_uistring(message), native::from_uistring(title),
                 wxCLOSE | wxICON_ERROR | wxCENTER);
#endif
}

bool confirm(const uistring& message, const uistring& title)
{
#if wxUSE_MSGDLG
    return wxMessageBox(native::from_uistring(message), native::from_uistring(title),
                        wxYES_NO | wxICON_WARNING | wxCENTER) == wxYES;
#else
    return false;
#endif
}

bool question(const uistring& message, const uistring& title)
{
#if wxUSE_MSGDLG
    return wxMessageBox(native::from_uistring(message), native::from_uistring(title),
                        wxYES_NO | wxICON_QUESTION | wxCENTER) == wxYES;
#else
    return false;
#endif
}

bool prompt(const uistring& message, const uistring& title, std::wstring& value)
{
    uistring str = value;
    if ( !prompt(message, title, str) )
        return false;

    value = str.wstring();
    return true;
}

bool prompt(const uistring& message, const uistring& title, uistring& value)
{
#if wxUSE_TEXTDLG
    wxTextEntryDialog dialog(NULL, native::from_uistring(message),
                             native::from_uistring(title),
                             native::from_uistring(value),
                             wxTextEntryDialogStyle | wxCENTER);

    if ( dialog.ShowModal() != wxID_OK )
        return false;

    value = native::to_uistring(dialog.GetValue());
    return true;
#else
    return false;
#endif
}

bool prompt_password(const uistring& message, const uistring& title, std::wstring& value)
{
    uistring str = value;
    if ( !prompt_password(message, title, str) )
        return false;

    value = str.wstring();
    return true;
}

bool prompt_password(const uistring& message, const uistring& title, uistring& value)
{
#if wxUSE_TEXTDLG
    wxPasswordEntryDialog dialog(NULL, native::from_uistring(message),
                                 native::from_uistring(title),
                                 native::from_uistring(value),
                                 wxTextEntryDialogStyle | wxCENTER);

    if ( dialog.ShowModal() != wxID_OK )
        return false;

    value = native::to_uistring(dialog.GetValue());
    return true;
#else
    return false;
#endif
}

bool prompt_filename(const uistring& title, std::wstring& value)
{
    uistring str = value;
    if ( !prompt_filename(title, str) )
        return false;

    value = str.wstring();
    return true;
}

bool prompt_filename(const uistring& title, uistring& value)
{
#if wxUSE_FILEDLG
    wxString str = wxFileSelector(native::from_uistring(title), wxString(), native::from_uistring(value));
    value = native::to_uistring(str);
    return !str.empty();
#else
    return false;
#endif
}

bool prompt_directory(const uistring& title, std::wstring& value)
{
    uistring str = value;
    if ( !prompt_directory(title, str) )
        return false;

    value = str.wstring();
    return true;
}

bool prompt_directory(const uistring& title, uistring& value)
{
#if wxUSE_DIRDLG
    wxString str = wxDirSelector(native::from_uistring(title), native::from_uistring(value));
    value = native::to_uistring(str);
    return !str.empty();
#else
    return false;
#endif
}

} // namespace ui
} // namespace boost
