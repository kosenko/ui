// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/image_widget.hpp>
#include <boost/ui/native/widget.hpp>

#include <wx/statbmp.h>

namespace boost {
namespace ui    {

#if wxUSE_STATBMP
class image_widget::detail_impl : public detail::widget_detail<wxStaticBitmap>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(new wxStaticBitmap(native::from_widget(parent),
            wxID_ANY, wxBitmap()));
    }
    explicit detail_impl(widget& parent, const ui::image& img)
    {
        const wxBitmap bitmap = img.valid()
            ? *static_cast<const wxBitmap*>(img.native_handle())
            : wxBitmap();
        set_native_handle(new wxStaticBitmap(native::from_widget(parent),
            wxID_ANY, bitmap));
    }
    void image(const ui::image& img)
    {
        wxCHECK(m_native, );
        wxCHECK(img.valid(), );
        m_native->SetBitmap(*static_cast<const wxBitmap*>( img.native_handle() ));
    }
    void clear()
    {
        wxCHECK(m_native, );
        m_native->SetBitmap(wxBitmap());
    }
};
#endif

image_widget::detail_impl* image_widget::get_impl()
{
#if wxUSE_STATBMP
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const image_widget::detail_impl* image_widget::get_impl() const
{
#if wxUSE_STATBMP
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

image_widget& image_widget::create(widget& parent)
{
#if wxUSE_STATBMP
    detail_set_detail_impl(new detail_impl(parent));
#endif

    return *this;
}

image_widget& image_widget::create(widget& parent, const ui::image& img)
{
#if wxUSE_STATBMP
    detail_set_detail_impl(new detail_impl(parent, img));
#endif

    return *this;
}

image_widget& image_widget::image(const ui::image& img)
{
#if wxUSE_STATBMP
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->image(img);
#endif

    return *this;
}

void image_widget::clear()
{
#if wxUSE_STATBMP
    detail_impl* impl = get_impl();
    wxCHECK(impl, );

    impl->clear();
#endif

}

} // namespace ui
} // namespace boost
