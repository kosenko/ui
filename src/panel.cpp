// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/panel.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/panel.h>

namespace boost {
namespace ui    {

class panel::detail_impl : public detail::widget_detail<wxPanel>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(new wxPanel(native::from_widget(parent)));
    }
};

panel& panel::create(widget& parent)
{
    detail_set_detail_impl(new detail_impl(parent));

    return *this;
}

} // namespace ui
} // namespace boost
