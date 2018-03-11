// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/combo_box.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/combobox.h>

namespace boost {
namespace ui    {

#if wxUSE_COMBOBOX

class combo_box::detail_impl : public detail::widget_detail<wxComboBox>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(new wxComboBox(native::from_widget(parent), wxID_ANY));
    }
    explicit detail_impl(widget& parent, const uistring& txt,
                         const std::vector<uistring>& options)
    {
        set_native_handle(new wxComboBox(native::from_widget(parent), wxID_ANY,
               native::from_uistring(txt),
               wxDefaultPosition, wxDefaultSize,
               native::from_vector_uistring(options)));
    }
    void text(const uistring& txt)
    {
        wxCHECK(m_native, );
        m_native->ChangeValue(native::from_uistring(txt));
    }
    uistring text() const
    {
        wxCHECK(m_native, uistring());
        return native::to_uistring(m_native->GetValue());
    }
};

#endif

combo_box::detail_impl* combo_box::get_impl()
{
#if wxUSE_COMBOBOX
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const combo_box::detail_impl* combo_box::get_impl() const
{
#if wxUSE_COMBOBOX
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

combo_box& combo_box::create(widget& parent)
{
#if wxUSE_COMBOBOX
    detail_set_detail_impl(new detail_impl(parent));
#endif

    return *this;
}

combo_box& combo_box::create(widget& parent, const uistring& txt,
                             const std::vector<uistring>& options)
{
#if wxUSE_COMBOBOX
    detail_set_detail_impl(new detail_impl(parent, txt, options));
#endif

    return *this;
}

combo_box& combo_box::text(const uistring& txt)
{
#if wxUSE_COMBOBOX
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->text(txt);
#endif

    return *this;
}

uistring combo_box::text() const
{
#if wxUSE_COMBOBOX
    const detail_impl* impl = get_impl();
    wxCHECK(impl, uistring());

    return impl->text();
#else
    return uistring();
#endif
}

void combo_box::on_select_raw(const boost::function<void()>& handler)
{
#if wxUSE_COMBOBOX
    native::bind_helper(*this, wxEVT_COMBOBOX, handler);
#endif
}

void combo_box::on_select_event_raw(const boost::function<void(index_event&)>& handler)
{
#if wxUSE_COMBOBOX
    native::bind_event_helper(*this, wxEVT_COMBOBOX, handler);
#endif
}

} // namespace ui
} // namespace boost
