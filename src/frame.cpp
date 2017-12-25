// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/frame.hpp>
#include <boost/ui/event_loop.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/frame.h>
#include <wx/evtloop.h>

#include "res/boost.xpm"

namespace boost {
namespace ui    {

class frame::detail_impl : public detail::window_detail<wxFrame>
{
public:
    explicit detail_impl(const uistring& title)
    {
        wxFrame* w = new wxFrame(NULL, wxID_ANY, native::from_uistring(title),
               wxDefaultPosition, wxDefaultSize,
               wxDEFAULT_FRAME_STYLE
              );
        w->SetIcon(boost_xpm);
        set_native_handle(w);

        w->Bind(wxEVT_CLOSE_WINDOW, &detail_impl::on_close, this);
    }
    virtual ~detail_impl()
    {
        delete_native();
    }
    void show_modal()
    {
        wxCHECK(m_native, );
        m_native->Show();

        m_modal_loop.run();
    }

private:
    void on_close(wxCloseEvent& e)
    {
        e.Skip();

        m_modal_loop.exit();
    }

    event_loop m_modal_loop;
};

frame& frame::create(const uistring& title)
{
    detail_set_detail_impl(new detail_impl(title));

    return *this;
}

} // namespace ui
} // namespace boost
