// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/hyperlink.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/hyperlink.h>

namespace boost {
namespace ui    {

#if wxUSE_HYPERLINKCTRL

class hyperlink::detail_impl : public detail::widget_detail<wxHyperlinkCtrl>
{
public:
    explicit detail_impl(widget& parent,
                         const uistring& url, const uistring& text)
    {
        set_native_handle(new wxHyperlinkCtrl(native::from_widget(parent),
            wxID_ANY,
            native::from_uistring(text), native::from_uistring(url)));
    }
};

#endif

hyperlink& hyperlink::create(widget& parent,
                             const uistring& url, const uistring& text)
{
#if wxUSE_HYPERLINKCTRL
    detail_set_detail_impl(new detail_impl(parent, url, text));
#endif

    return *this;
}

} // namespace ui
} // namespace boost
