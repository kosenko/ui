// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/dialog.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/dialog.h>

#include "res/boost.xpm"

namespace boost {
namespace ui    {

class dialog::detail_impl : public detail::window_detail<wxDialog>
{
public:
    explicit detail_impl(const uistring& title)
    {
        wxDialog* w = new wxDialog(NULL, wxID_ANY,
            native::from_uistring(title),
            wxDefaultPosition, wxDefaultSize,
            wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER |
            wxMAXIMIZE_BOX | wxMINIMIZE_BOX);
        w->SetIcon(boost_xpm);
        set_native_handle(w);
    }
    virtual ~detail_impl()
    {
        delete_native();
    }
    void show_modal()
    {
        wxCHECK(m_native, );
        m_native->ShowModal();
    }
};

dialog::detail_impl* dialog::get_impl()
{
    return get_detail_impl<detail_impl>();
}

dialog& dialog::create(const uistring& title)
{
    detail_set_detail_impl(new detail_impl(title));

    return *this;
}

} // namespace ui
} // namespace boost
