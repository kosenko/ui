// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/locale.hpp>

#include <wx/intl.h>
#include <wx/log.h>

#include <stdexcept> // std::runtime_error

namespace boost {
namespace ui    {

std::locale getloc()
{
    const wxLanguageInfo* info = wxLocale::GetLanguageInfo(wxLocale::GetSystemLanguage());
    wxCHECK_MSG(info, std::locale(), "System language has no valid info");

    wxString localeName = info->GetLocaleName();
#ifndef BOOST_WINDOWS
    localeName << wxS(".UTF-8");
#endif
    try
    {
        return std::locale(localeName.ToAscii());
    }
    catch(...)
    {
        wxLogDebug(wxS("Invalid std::locale name: '%s'"), localeName);
        return std::locale();
    }
}

} // namespace ui
} // namespace boost
