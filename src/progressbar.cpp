// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/progressbar.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/gauge.h>

namespace boost {
namespace ui    {

#if wxUSE_GAUGE

class progressbar::detail_impl : public detail::widget_detail<wxGauge>
{
public:
    explicit detail_impl(widget& parent, bool horizontal, value_type initial,
                         value_type max)
    {
        wxGauge* w = new wxGauge(native::from_widget(parent),
            wxID_ANY, max, wxDefaultPosition, wxDefaultSize,
            horizontal ? wxGA_HORIZONTAL : wxGA_VERTICAL);
        w->SetValue(initial);
        set_native_handle(w);
    }
    void value(value_type value)
    {
        wxCHECK(m_native, );
        m_native->SetValue(value);
    }
    value_type value() const
    {
        wxCHECK(m_native, -1);
        return m_native->GetValue();
    }
    value_type max() const
    {
        wxCHECK(m_native, -1);
        return m_native->GetRange();
    }
};

#endif

progressbar::detail_impl* progressbar::get_impl()
{
#if wxUSE_GAUGE
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const progressbar::detail_impl* progressbar::get_impl() const
{
#if wxUSE_GAUGE
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void progressbar::detail_create(widget& parent, bool horizontal, value_type initial,
                                value_type max)

{
    check_range(initial, max);

#if wxUSE_GAUGE
    detail_set_detail_impl(new detail_impl(parent, horizontal, initial, max));
#endif
}

progressbar& progressbar::value(value_type value)
{
    check_range(value);

#if wxUSE_GAUGE
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->value(value);
#endif

    return *this;
}

progressbar::value_type progressbar::value() const
{
#if wxUSE_GAUGE
    const detail_impl* impl = get_impl();
    wxCHECK(impl, -1);

    return impl->value();
#else
    return -1;
#endif
}

progressbar::value_type progressbar::max() const
{
#if wxUSE_GAUGE
    const detail_impl* impl = get_impl();
    wxCHECK(impl, -1);

    return impl->max();
#else
    return -1;
#endif
}

void progressbar::check_range(value_type value, value_type max)
{
    if ( value < 0 || value > max )
        BOOST_THROW_EXCEPTION(std::out_of_range("ui::progressbar::check_range(): invalid value"));
}

} // namespace ui
} // namespace boost
