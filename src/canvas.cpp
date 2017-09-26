// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/canvas.hpp>
#include <boost/ui/painter.hpp>
#include <boost/ui/native/impl/canvas.hpp>

#include <wx/dcclient.h>
#include <wx/dcmemory.h>

namespace boost  {
namespace ui     {

ui::painter canvas::painter()
{
    return ui::painter(get_impl());
}

detail::painter_impl* canvas::get_impl()
{
    return get_detail_impl<detail::painter_impl>();
}

canvas& canvas::create(widget& parent)
{
    detail_set_detail_impl(new detail::painter_impl(parent));

    return *this;
}

} // namespace ui
} // namespace boost
