// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/line.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/statline.h>

namespace boost {
namespace ui    {

#if wxUSE_STATLINE

class line_widget::detail_impl : public detail::widget_detail<wxStaticLine>
{
public:
    explicit detail_impl(widget& parent, bool horizontal)
    {
        set_native_handle(new wxStaticLine(native::from_widget(parent),
            wxID_ANY, wxDefaultPosition, wxDefaultSize,
            horizontal ? wxLI_HORIZONTAL : wxLI_VERTICAL));
    }
};

#endif

void line_widget::detail_create(widget& parent, bool horizontal)
{
#if wxUSE_STATLINE
    detail_set_detail_impl(new detail_impl(parent, horizontal));
#endif
}

} // namespace ui
} // namespace boost
