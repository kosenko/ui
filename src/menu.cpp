// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/menu.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/menu.h>

namespace boost {
namespace ui    {

#if wxUSE_MENUS

class menu::native_impl : public wxMenu, private detail::memcheck
{
public:
};

class menu::item::native_impl : public wxMenuItem
{
public:
    native_impl(const uistring& text)
        : wxMenuItem(NULL, wxID_ANY, native::from_uistring(text)) {}
};

#endif

menu::menu()
{
#if wxUSE_MENUS
    m_impl = new native_impl;
#endif
}

menu::~menu()
{
#if wxUSE_MENUS
    delete m_impl;
#endif
}

menu& menu::append(const item& i)
{
#if wxUSE_MENUS
    m_impl->Append(i.m_impl);
#endif
    return *this;
}

void menu::popup(widget& w)
{
    wxWindow *window = native::from_widget(w);
    wxCHECK(window, );

#if wxUSE_MENUS
    window->PopupMenu(m_impl);
#endif
}

menu::item::item(const uistring& text)
{
#if wxUSE_MENUS
    m_impl = new native_impl(text);
#endif
}

} // namespace ui
} // namespace boost
