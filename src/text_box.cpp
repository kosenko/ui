// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/text_box.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/textctrl.h>

namespace boost {
namespace ui    {

#if wxUSE_TEXTCTRL

class text_box_base::detail_impl : public detail::widget_detail<wxTextCtrl>
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
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->Clear();
    }
    void text(const uistring& text)
    {
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->ChangeValue(native::from_uistring(text));
    }
    uistring text() const
    {
        wxCHECK_MSG(m_native, uistring(), "Widget should be created");
        return native::to_uistring(m_native->GetValue());
    }
    void placeholder(const uistring& text)
    {
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->SetHint(native::from_uistring(text));
    }
    uistring placeholder() const
    {
        wxCHECK_MSG(m_native, uistring(), "Widget should be created");
        return native::to_uistring(m_native->GetHint());
    }
};

#endif

text_box_base::detail_impl* text_box_base::get_impl()
{
#if wxUSE_TEXTCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const text_box_base::detail_impl* text_box_base::get_impl() const
{
#if wxUSE_TEXTCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void text_box_base::detail_create(widget& parent, const uistring& text, int style)
{
#if wxUSE_TEXTCTRL
    detail_set_detail_impl(new detail_impl(parent, text, style));
#endif
}

void text_box_base::clear()
{
#if wxUSE_TEXTCTRL
    detail_impl* impl = get_impl();
    wxCHECK_RET(impl, "Widget should be created");

    impl->clear();
#endif
}

text_box_base& text_box_base::text(const uistring& text)
{
#if wxUSE_TEXTCTRL
    detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->text(text);
#endif

    return *this;
}

uistring text_box_base::text() const
{
#if wxUSE_TEXTCTRL
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, uistring(), "Widget should be created");

    return impl->text();
#else
    return uistring();
#endif
}

text_box_base& text_box_base::detail_placeholder(const uistring& text)
{
#if wxUSE_TEXTCTRL
    detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->placeholder(text);
#endif

    return *this;
}

uistring text_box_base::detail_placeholder() const
{
#if wxUSE_TEXTCTRL
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, uistring(), "Widget should be created");

    return impl->placeholder();
#else
    return uistring();
#endif
}

void text_box_base::on_edit_raw(const boost::function<void()>& handler)
{
#if wxUSE_TEXTCTRL
    native::bind_helper(*this, wxEVT_TEXT, handler);
#endif
}

string_box& string_box::create(widget& parent, const uistring& text)
{
    detail_create(parent, text, 0);

    return *this;
}

password_box& password_box::create(widget& parent, const uistring& text)
{
#if wxUSE_TEXTCTRL
    detail_create(parent, text, wxTE_PASSWORD);
#else
    detail_create(parent, text, 0);
#endif

    return *this;
}

text_box& text_box::create(widget& parent, const uistring& text)
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
