// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/progress_bar.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/gauge.h>

namespace boost {
namespace ui    {

#if wxUSE_GAUGE

class progress_bar::detail_impl : public detail::widget_detail<wxGauge>
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
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->SetValue(value);
    }
    value_type value() const
    {
        wxCHECK_MSG(m_native, -1, "Widget should be created");
        return m_native->GetValue();
    }
    value_type max() const
    {
        wxCHECK_MSG(m_native, -1, "Widget should be created");
        return m_native->GetRange();
    }
};

#endif

progress_bar::detail_impl* progress_bar::get_impl()
{
#if wxUSE_GAUGE
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const progress_bar::detail_impl* progress_bar::get_impl() const
{
#if wxUSE_GAUGE
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void progress_bar::detail_create(widget& parent, bool horizontal, value_type initial,
                                value_type max)

{
    check_range(initial, max);

#if wxUSE_GAUGE
    detail_set_detail_impl(new detail_impl(parent, horizontal, initial, max));
#endif
}

progress_bar& progress_bar::value(value_type value)
{
    check_range(value);

#if wxUSE_GAUGE
    detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->value(value);
#endif

    return *this;
}

progress_bar::value_type progress_bar::value() const
{
#if wxUSE_GAUGE
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, -1, "Widget should be created");

    return impl->value();
#else
    return -1;
#endif
}

progress_bar::value_type progress_bar::max() const
{
#if wxUSE_GAUGE
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, -1, "Widget should be created");

    return impl->max();
#else
    return -1;
#endif
}

void progress_bar::check_range(value_type value, value_type max)
{
    if ( value < 0 || value > max )
        BOOST_THROW_EXCEPTION(std::out_of_range("ui::progress_bar::check_range(): invalid value"));
}

} // namespace ui
} // namespace boost
