// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/label.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/stattext.h>

namespace boost {
namespace ui    {

#if wxUSE_STATTEXT

class label::detail_impl : public detail::widget_detail<wxStaticText>
{
public:
    void create(widget& parent, const uistring& txt)
    {
        m_txt = txt;
        set_native_handle(new wxStaticText(native::from_widget(parent),
            wxID_ANY, native::from_uistring(txt),
            wxDefaultPosition, wxDefaultSize,
            style_flags(wxST_NO_AUTORESIZE) ));
    }
    void text(const uistring& txt)
    {
        if ( m_native  )
            m_native->SetLabel(native::from_uistring(txt));
        else
            m_txt = txt;
    }
    uistring text() const
    {
        if ( m_native )
            return native::to_uistring(m_native->GetLabel());
        else
            return m_txt;
    }

protected:
    virtual void do_create_native(widget& parent)
    {
        create(parent, m_txt);
        create_base();
    }

private:
    uistring m_txt; // TODO: Move to cache
};

#endif

label::detail_impl* label::get_impl()
{
#if wxUSE_STATTEXT
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const label::detail_impl* label::get_impl() const
{
#if wxUSE_STATTEXT
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void label::init()
{
#if wxUSE_STATTEXT
    detail_set_detail_impl(new detail_impl);
#endif
}

label& label::create(widget& parent, const uistring& txt)
{
#if wxUSE_STATTEXT
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->create(parent, txt);
#endif

    return *this;
}

label& label::text(const uistring& txt)
{
#if wxUSE_STATTEXT
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->text(txt);
#endif

    return *this;
}

uistring label::text() const
{
#if wxUSE_STATTEXT
    const detail_impl* impl = get_impl();
    wxCHECK(impl, uistring());

    return impl->text();
#else
    return uistring();
#endif
}

} // namespace ui
} // namespace boost
