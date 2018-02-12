// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/window.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>

#include <boost/bind.hpp>

#include <wx/toplevel.h>

namespace boost {
namespace ui    {

namespace native {

template <>
void event_functor_event<wxCloseEvent, close_event>::init(close_event& uievent, wxCloseEvent& wxevent)
{
    uievent.m_veto_fn = boost::bind(&wxCloseEvent::Veto, boost::ref(wxevent), _1);
    uievent.m_skip_fn = boost::bind(&wxCloseEvent::Skip, boost::ref(wxevent), _1);
}

} // namespace native

close_event::~close_event()
{
    if ( m_veto )
    {
        m_veto_fn(true);
        m_skip_fn(false);
    }
}

namespace {

wxTopLevelWindow* get_impl(widget& w)
{ return static_cast<wxTopLevelWindow*>(w.native_handle()); }

const wxTopLevelWindow* get_impl(const widget& w)
{ return static_cast<const wxTopLevelWindow*>(w.native_handle()); }

} // namespace unnamed

window& window::title(const uistring& title)
{
    wxTopLevelWindow* impl = get_impl(*this);
    wxCHECK(impl, *this);

    impl->SetTitle(native::from_uistring(title));

    return *this;
}

uistring window::title() const
{
    const wxTopLevelWindow* impl = get_impl(*this);
    wxCHECK(impl, uistring());

    return native::to_uistring(impl->GetTitle());
}

void window::show_modal()
{
    detail::window_detail_base* impl =
        get_detail_impl<detail::window_detail_base>();
    wxCHECK(impl, );

    impl->show_modal();
}

bool window::close()
{
    wxTopLevelWindow* impl = get_impl(*this);
    wxCHECK(impl, true);

    return impl->Close();
}

void window::on_close_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_CLOSE_WINDOW, handler);
}

void window::on_close_event_raw(const boost::function<void(close_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_CLOSE_WINDOW, handler);
}

} // namespace ui
} // namespace boost
