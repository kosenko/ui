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
    typedef native_impl this_type;

public:
    native_impl()
    {
        Bind(wxEVT_MENU, &this_type::on_menu, this);
    }

private:
    void on_menu(wxCommandEvent& event);
};

class menu::item::native_impl : public wxMenuItem
{
public:
    native_impl(const uistring& text)
        : wxMenuItem(NULL, wxID_ANY, native::from_uistring(text)) {}

    void on_menu();

    typedef std::vector< boost::function<void()> > menu_handlers_type;
    menu_handlers_type m_menu_handlers;
};

void menu::native_impl::on_menu(wxCommandEvent& event)
{
    wxMenuItem* rawitem = FindItem(event.GetId());
    wxCHECK(rawitem, );

    item::native_impl* item = dynamic_cast<item::native_impl*>(rawitem);
    wxCHECK(item, );

    item->on_menu();
}

void menu::item::native_impl::on_menu()
{
    for ( menu_handlers_type::const_reverse_iterator iter = m_menu_handlers.rbegin();
            iter != m_menu_handlers.rend(); ++iter )
    {
        (*iter)();
    }
}

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

void menu::item::on_press_raw(const boost::function<void()>& handler)
{
    wxCHECK(m_impl, );

    m_impl->m_menu_handlers.push_back(handler);
}

} // namespace ui
} // namespace boost
