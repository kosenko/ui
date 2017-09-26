// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/layout.hpp>
#include <boost/ui/widget.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/sizer.h>

namespace boost {
namespace ui    {

class layout::item::impl : public wxSizerFlags, private detail::memcheck
{
public:
    impl();

    void margin_px(int top, int right, int bottom, int left);

    impl& get(bool is_visual, bool is_vertical);

private:
    bool m_default_margin;
};

layout::item::impl::impl() : m_default_margin(true)
{
    Align(wxALIGN_CENTER_VERTICAL);
}

void layout::item::impl::margin_px(int top, int right, int bottom, int left)
{
    int direction = 0;
    int size = 0;

    if ( top )
    {
        direction |= wxTOP;
        if ( top > size )
            size = top;
    }

    if ( right )
    {
        direction |= wxRIGHT;
        if ( right > size )
            size = right;
    }

    if ( bottom )
    {
        direction |= wxBOTTOM;
        if ( bottom > size )
            size = bottom;
    }

    if ( left )
    {
        direction |= wxLEFT;
        if ( left > size )
            size = left;
    }

    Border(direction, size);
    m_default_margin = false;
}

layout::item::impl& layout::item::impl::get(bool is_visual, bool is_vertical)
{
    if ( m_default_margin )
    {
        if ( is_visual )
            Border();
        else
            Border(wxALL, 0);
    }

    // Fix box sizer insert assertion failures
    if ( is_vertical )
        Top();
    else if ( GetFlags() & wxEXPAND )
        Top();

    return *this;
}

layout::item::item()
{
    m_impl = new impl;
    m_widget = NULL;
    m_layout = NULL;
}

layout::item::item(const widget& w)
{
    m_impl = new impl;
    m_widget = const_cast<widget*>(&w);
    m_layout = NULL;
}

layout::item::item(const box_layout& l)
{
    m_impl = new impl;
    m_widget = NULL;
    m_layout = const_cast<box_layout*>(&l);
}

layout::item::item(const item& other)
{
    m_impl = new impl;
    *m_impl = *other.m_impl;
    m_widget = other.m_widget;
    m_layout = other.m_layout;
}

layout::item::~item()
{
    delete m_impl;
}

layout::item& layout::item::operator=(const item& other)
{
    *m_impl  = *other.m_impl;
    m_widget = other.m_widget;
    m_layout = other.m_layout;
    return *this;
}

layout::item& layout::item::append(const item& item)
{
    wxCHECK(m_layout, *this);
    m_layout->append(item);
    return *this;
}

layout::item& layout::item::margin(int top, int right, int bottom, int left)
{
    return margin_px(top    * wxSizerFlags::GetDefaultBorder(),
                     right  * wxSizerFlags::GetDefaultBorder(),
                     bottom * wxSizerFlags::GetDefaultBorder(),
                     left   * wxSizerFlags::GetDefaultBorder());
}

// Arguments order is same as in CSS margin property
layout::item& layout::item::margin_px(int top, int right, int bottom, int left)
{
    m_impl->margin_px(top, right, bottom, left);
    return *this;
}

layout::item& layout::item::stretch(int value)
{
    m_impl->Proportion(value);
    return *this;
}

layout::item& layout::item::left()
{
    m_impl->Left();
    return *this;
}

layout::item& layout::item::right()
{
    m_impl->Right();
    return *this;
}

layout::item& layout::item::top()
{
    m_impl->Top();
    return *this;
}

layout::item& layout::item::bottom()
{
    m_impl->Bottom();
    return *this;
}

layout::item& layout::item::vcenter()
{
    m_impl->Align(wxALIGN_CENTER_VERTICAL);
    return *this;
}

layout::item& layout::item::hcenter()
{
    m_impl->Align(wxALIGN_CENTER_HORIZONTAL);
    return *this;
}

layout::item& layout::item::center()
{
    m_impl->Center();
    return *this;
}

layout::item& layout::item::justify()
{
    m_impl->Expand();
    return *this;
}

class box_layout::impl : public wxBoxSizer, private detail::memcheck
{
public:
    impl(bool horizontal) : wxBoxSizer(horizontal ? wxHORIZONTAL : wxVERTICAL)
    {
    }
};

box_layout::box_layout(bool horizontal)
{
    m_impl = new impl(horizontal); // TODO: Leaks possible
}

box_layout::box_layout(widget& parent, bool horizontal)
{
    m_impl = new impl(horizontal);
    native::from_widget(parent)->SetSizer(m_impl);
}

static void move_on_top_in_tab_order(wxWindow* window)
{
    wxCHECK(window, );

    wxWindow* parent = window->GetParent();
    wxCHECK(parent, );

    const wxWindowList& children = window->GetParent()->GetChildren();
    wxASSERT_LEVEL_2(!children.empty());

    window->MoveAfterInTabOrder(children[children.size() - 1]);
}

static void move_on_top_in_tab_order(wxSizer* sizer)
{
    wxCHECK(sizer, );

    const wxSizerItemList& children = sizer->GetChildren();
    for ( wxSizerItemList::const_iterator iter = children.begin();
        iter != children.end(); ++iter )
    {
        if ( (**iter).IsWindow() )
            move_on_top_in_tab_order((**iter).GetWindow());
        else if ( (**iter).IsSizer() )
            move_on_top_in_tab_order((**iter).GetSizer());
    }
}

box_layout& box_layout::append(const item& item)
{
    if ( item.m_widget )
    {
        wxWindow* window = native::from_widget(const_cast<widget&>(*item.m_widget));
        move_on_top_in_tab_order(window);

        m_impl->Add(window, item.m_impl->get(true, m_impl->IsVertical()));
    }
    else if ( item.m_layout )
    {
        wxSizer* sizer = item.m_layout->m_impl;
        move_on_top_in_tab_order(sizer);

        m_impl->Add(sizer, item.m_impl->get(false, m_impl->IsVertical()));
    }
    else
    {
        m_impl->Add(0, 0, item.m_impl->get(false, m_impl->IsVertical()));
    }

    return *this;
}

} // namespace ui
} // namespace boost
