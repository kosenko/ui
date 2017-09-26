// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/textbox.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/textctrl.h>

namespace boost {
namespace ui    {

#if wxUSE_TEXTCTRL

class textbox_base::detail_impl : public detail::widget_detail<wxTextCtrl>
{
public:
    explicit detail_impl(widget& parent, const uistring& text, int style)
    {
        set_native_handle(new wxTextCtrl(native::from_widget(parent),
               wxID_ANY, native::from_uistring(text),
               wxDefaultPosition, wxDefaultSize, style));
    }
    void clear()
    {
        wxCHECK(m_native, );
        m_native->Clear();
    }
    void text(const uistring& text)
    {
        wxCHECK(m_native, );
        m_native->ChangeValue(native::from_uistring(text));
    }
    uistring text() const
    {
        wxCHECK(m_native, uistring());
        return native::to_uistring(m_native->GetValue());
    }
};

#endif

textbox_base::detail_impl* textbox_base::get_impl()
{
#if wxUSE_TEXTCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const textbox_base::detail_impl* textbox_base::get_impl() const
{
#if wxUSE_TEXTCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void textbox_base::detail_create(widget& parent, const uistring& text, int style)
{
#if wxUSE_TEXTCTRL
    detail_set_detail_impl(new detail_impl(parent, text, style));
#endif
}

void textbox_base::clear()
{
#if wxUSE_TEXTCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, );

    impl->clear();
#endif
}

textbox_base& textbox_base::text(const uistring& text)
{
#if wxUSE_TEXTCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->text(text);
#endif

    return *this;
}

uistring textbox_base::text() const
{
#if wxUSE_TEXTCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, uistring());

    return impl->text();
#else
    return uistring();
#endif
}

textbox_base& textbox_base::on_edit(const boost::function<void()>& handler)
{
#if wxUSE_TEXTCTRL
    native::bind_helper(*this, wxEVT_TEXT, handler);
#endif

    return *this;
}

stringbox& stringbox::create(widget& parent, const uistring& text)
{
    detail_create(parent, text, 0);

    return *this;
}

passwordbox& passwordbox::create(widget& parent, const uistring& text)
{
#if wxUSE_TEXTCTRL
    detail_create(parent, text, wxTE_PASSWORD);
#else
    detail_create(parent, text, 0);
#endif

    return *this;
}

textbox& textbox::create(widget& parent, const uistring& text)
{
#if wxUSE_TEXTCTRL
    detail_create(parent, text, wxTE_MULTILINE);
#else
    detail_create(parent, text, 0);
#endif

    return *this;
}

} // namespace ui
} // namespace boost
