// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/slider.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/slider.h>

namespace boost {
namespace ui    {

#if wxUSE_SLIDER

class slider::detail_impl : public detail::widget_detail<wxSlider>
{
public:
    explicit detail_impl(widget& parent, bool horizontal, value_type initial,
                         value_type min, value_type max)
    {
        set_native_handle(new wxSlider(native::from_widget(parent),
               wxID_ANY, initial, min, max,
               wxDefaultPosition, wxDefaultSize,
               horizontal ? wxSL_HORIZONTAL : wxSL_VERTICAL));
    }
    value_type value() const
    {
        wxCHECK(m_native, -1);
        return m_native->GetValue();
    }
    value_type min() const
    {
        wxCHECK(m_native, -1);
        return m_native->GetMin();
    }
    value_type max() const
    {
        wxCHECK(m_native, -1);
        return m_native->GetMax();
    }
};

#endif

slider::detail_impl* slider::get_impl()
{
#if wxUSE_SLIDER
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const slider::detail_impl* slider::get_impl() const
{
#if wxUSE_SLIDER
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void slider::detail_create(widget& parent, bool horizontal, value_type initial,
                           value_type min, value_type max)

{
    check_range(initial, min, max);

#if wxUSE_SLIDER
    detail_set_detail_impl(new detail_impl(parent, horizontal, initial, min, max));
#endif
}

slider::value_type slider::value() const
{
#if wxUSE_SLIDER
    const detail_impl* impl = get_impl();
    wxCHECK(impl, -1);

    return impl->value();
#else
    return -1;
#endif
}

slider::value_type slider::min() const
{
#if wxUSE_SLIDER
    const detail_impl* impl = get_impl();
    wxCHECK(impl, -1);

    return impl->min();
#else
    return -1;
#endif
}

slider::value_type slider::max() const
{
#if wxUSE_SLIDER
    const detail_impl* impl = get_impl();
    wxCHECK(impl, -1);

    return impl->max();
#else
    return -1;
#endif
}

void slider::check_range(value_type value, value_type min, value_type max)
{
    if ( value < min || value > max )
        BOOST_THROW_EXCEPTION(std::out_of_range("ui::slider::check_range(): invalid value"));
}

slider& slider::on_slide(const boost::function<void()>& handler)
{
#if wxUSE_SLIDER
    native::bind_helper(*this, wxEVT_SLIDER, handler);
#endif

    return *this;
}

slider& slider::on_slide_end(const boost::function<void()>& handler)
{
#if wxUSE_SLIDER
    native::bind_helper(*this, wxEVT_SCROLL_THUMBRELEASE, handler);
#endif

    return *this;
}

} // namespace ui
} // namespace boost
