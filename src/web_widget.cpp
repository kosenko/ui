// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/web_widget.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>

#include <wx/webview.h>

namespace boost {
namespace ui    {

#if wxUSE_WEBVIEW

class web_widget::detail_impl : public detail::widget_detail<wxWebView>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(wxWebView::New( native::from_widget(parent), wxID_ANY ));
    }
    void set_html(const uistring& html)
    {
        wxCHECK(m_native, );
        m_native->SetPage(native::from_uistring(html), wxString());
    }
    void load(const uistring& url)
    {
        wxCHECK(m_native, );
        m_native->LoadURL(native::from_uistring(url));
    }
};

#endif

web_widget::detail_impl* web_widget::get_impl()
{
#if wxUSE_WEBVIEW
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

web_widget& web_widget::create(widget& parent)
{
#if wxUSE_WEBVIEW
    detail_set_detail_impl(new detail_impl(parent));
#endif

    return *this;
}

web_widget& web_widget::html(const uistring& html)
{
#if wxUSE_WEBVIEW
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->set_html(html);
#endif

    return *this;
}

web_widget& web_widget::load(const uistring& url)
{
#if wxUSE_WEBVIEW
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->load(url);
#endif

    return *this;
}

} // namespace ui
} // namespace boost
