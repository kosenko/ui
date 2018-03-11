// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/button.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/button.h>

namespace boost {
namespace ui    {

#if wxUSE_BUTTON
class button::detail_impl : public detail::widget_detail<wxButton>
{
public:
    explicit detail_impl(widget& parent, const uistring& label)
    {
        set_native_handle(new wxButton(native::from_widget(parent),
            wxID_ANY, native::from_uistring(label)));
    }
};
#endif

button& button::create(widget& parent, const uistring& label)
{
#if wxUSE_BUTTON
    detail_set_detail_impl(new detail_impl(parent, label));
#endif

    return *this;
}

void button::on_press_raw(const boost::function<void()>& handler)
{
#if wxUSE_BUTTON
    native::bind_helper(*this, wxEVT_BUTTON, handler);
#endif
}

} // namespace ui
} // namespace boost
