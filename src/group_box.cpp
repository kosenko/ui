// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/group_box.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/statbox.h>

namespace boost {
namespace ui    {

#if wxUSE_STATBOX

class group_box::detail_impl : public detail::widget_detail<wxStaticBox>
{
public:
    explicit detail_impl(widget& parent, const uistring& title)
    {
        set_native_handle(new wxStaticBox(native::from_widget(parent),
            wxID_ANY, native::from_uistring(title)));
    }
};

#endif

group_box::detail_impl* group_box::get_impl()
{
#if wxUSE_STATBOX
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const group_box::detail_impl* group_box::get_impl() const
{
#if wxUSE_STATBOX
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

group_box& group_box::create(widget& parent, const uistring& title)
{
#if wxUSE_STATBOX
    detail_set_detail_impl(new detail_impl(parent, title));
#endif

    return *this;
}

} // namespace ui
} // namespace boost
