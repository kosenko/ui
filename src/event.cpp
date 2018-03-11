// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/event.hpp>
#include <boost/ui/native/event.hpp>

#include <wx/event.h>

namespace boost {
namespace ui    {

mouse_event::mouse_event() : m_x(-1), m_y(-1),
    m_left(false), m_right(false), m_middle(false)
{
}

namespace native {

template <>
void event_functor_event<wxCommandEvent, event>::init(event& uievent, wxCommandEvent& wxevent)
{
}

template <>
void event_functor_event<wxCommandEvent, index_event>::init(index_event& uievent, wxCommandEvent& wxevent)
{
    uievent.m_index = wxevent.GetInt();
}

template <>
void event_functor_event<wxKeyEvent, key_event>::init(key_event& uievent, wxKeyEvent& wxevent)
{
    uievent.m_code = wxevent.GetKeyCode();

#if wxUSE_UNICODE
    uievent.m_char = wxevent.GetUnicodeKey();
#endif

    uievent.m_ctrl  = wxevent.ControlDown();
    uievent.m_shift = wxevent.ShiftDown();
    uievent.m_alt   = wxevent.AltDown();
    uievent.m_meta  = wxevent.MetaDown();
}

template <>
void event_functor_event<wxMouseEvent, mouse_event>::init(mouse_event& uievent, wxMouseEvent& wxevent)
{
    uievent.m_x = wxevent.GetX();
    uievent.m_y = wxevent.GetY();
    uievent.m_left   = wxevent.LeftIsDown()   || wxevent.LeftUp();
    uievent.m_right  = wxevent.RightIsDown()  || wxevent.RightUp();
    uievent.m_middle = wxevent.MiddleIsDown() || wxevent.MiddleUp();
}

template <>
void event_functor_event<wxMouseEvent, wheel_event>::init(wheel_event& uievent, wxMouseEvent& wxevent)
{
    uievent.m_x = wxevent.GetX();
    uievent.m_y = wxevent.GetY();
    uievent.m_left   = wxevent.LeftIsDown()   || wxevent.LeftUp();
    uievent.m_right  = wxevent.RightIsDown()  || wxevent.RightUp();
    uievent.m_middle = wxevent.MiddleIsDown() || wxevent.MiddleUp();

    uievent.m_horizontal = wxevent.GetWheelAxis() == wxMOUSE_WHEEL_HORIZONTAL;
    uievent.m_delta = wxevent.GetWheelRotation();
    if ( uievent.m_horizontal )
        uievent.m_delta = -uievent.m_delta;
}

template <>
void event_functor_event<wxContextMenuEvent, mouse_event>::init(mouse_event& uievent, wxContextMenuEvent& wxevent)
{
    wxPoint pos = wxevent.GetPosition();

    wxWindow* window = dynamic_cast<wxWindow*>(wxevent.GetEventObject());
    wxCHECK(window, );
    pos = window->ScreenToClient(pos);

    uievent.m_x = pos.x;
    uievent.m_y = pos.y;
}

} // namespace native
} // namespace ui
} // namespace boost
