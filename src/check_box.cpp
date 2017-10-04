// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/check_box.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/checkbox.h>

namespace boost {
namespace ui    {

#if wxUSE_CHECKBOX

class check_box_base::detail_impl : public detail::widget_detail<wxCheckBox>
{
public:
    explicit detail_impl(widget& parent, const uistring& text,
                         bool is_tri_state)
    {
        set_native_handle(new wxCheckBox(native::from_widget(parent),
            wxID_ANY, native::from_uistring(text),
            wxDefaultPosition, wxDefaultSize,
            is_tri_state ? wxCHK_3STATE | wxCHK_ALLOW_3RD_STATE_FOR_USER
                         : wxCHK_3STATE));
    }
    void check(bool checked)
    {
        wxCHECK(m_native, );
        m_native->Set3StateValue(checked ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    }
    void indeterminate()
    {
        wxCHECK(m_native, );
        m_native->Set3StateValue(wxCHK_UNDETERMINED);
    }
    bool is_checked() const
    {
        wxCHECK(m_native, false);
        return m_native->Get3StateValue() == wxCHK_CHECKED;
    }
    bool is_unchecked() const
    {
        wxCHECK(m_native, false);
        return m_native->Get3StateValue() == wxCHK_UNCHECKED;
    }
    bool is_indeterminate() const
    {
        wxCHECK(m_native, false);
        return m_native->Get3StateValue() == wxCHK_UNDETERMINED;
    }
};

#endif

check_box_base::detail_impl* check_box_base::get_impl()
{
#if wxUSE_CHECKBOX
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const check_box_base::detail_impl* check_box_base::get_impl() const
{
#if wxUSE_CHECKBOX
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

void check_box_base::detail_create(widget& parent, const uistring& text, bool is_tri_state)
{
#if wxUSE_CHECKBOX
    detail_set_detail_impl(new detail_impl(parent, text, is_tri_state));
#endif
}

check_box_base& check_box_base::check(bool checked)
{
#if wxUSE_CHECKBOX
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->check(checked);
#endif

    return *this;
}

check_box_base& check_box_base::indeterminate()
{
#if wxUSE_CHECKBOX
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    impl->indeterminate();
#endif

    return *this;
}

bool check_box_base::is_checked() const
{
#if wxUSE_CHECKBOX
    const detail_impl* impl = get_impl();
    wxCHECK(impl, false);

    return impl->is_checked();
#else
    return false;
#endif
}

bool check_box_base::is_unchecked() const
{
#if wxUSE_CHECKBOX
    const detail_impl* impl = get_impl();
    wxCHECK(impl, false);

    return impl->is_unchecked();
#else
    return false;
#endif
}

bool check_box_base::is_indeterminate() const
{
#if wxUSE_CHECKBOX
    const detail_impl* impl = get_impl();
    wxCHECK(impl, false);

    return impl->is_indeterminate();
#else
    return false;
#endif
}


check_box_base& check_box_base::on_toggle(const boost::function<void()>& handler)
{
#if wxUSE_CHECKBOX
    native::bind_helper(*this, wxEVT_CHECKBOX, handler);
#endif

    return *this;
}

} // namespace ui
} // namespace boost
