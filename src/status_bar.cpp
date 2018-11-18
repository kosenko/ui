// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/status_bar.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/statusbr.h>

namespace boost {
namespace ui    {

#if wxUSE_STATUSBAR

class status_bar::native_impl : public wxStatusBar, private detail::memcheck
{
public:
    native_impl(widget& parent) : wxStatusBar(native::from_widget(parent))
    {
        SetFieldsCount(1);
    }
};

#endif // wxUSE_STATUSBAR

status_bar::status_bar() : m_impl(NULL)
{
}

status_bar::status_bar(const status_bar& other)
{
    m_impl = other.m_impl;
}

void status_bar::create(widget& parent)
{
#if wxUSE_STATUSBAR
    m_impl = new native_impl(parent);
#else
    m_impl = NULL;
#endif
}

status_bar::~status_bar()
{
    // It should be deleted by frame
    //delete m_impl;
}

status_bar& status_bar::text(const uistring& text)
{
    wxCHECK_MSG(m_impl, *this, "Widget should be created");
#if wxUSE_STATUSBAR
    m_impl->SetStatusText(native::from_uistring(text));
#endif
    return *this;
}

uistring status_bar::text() const
{
    wxCHECK_MSG(m_impl, uistring(), "Widget should be created");
#if wxUSE_STATUSBAR
    return native::to_uistring(m_impl->GetStatusText());
#else
    return uistring();
#endif
}

} // namespace ui
} // namespace boost
