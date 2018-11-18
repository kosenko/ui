// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

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
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->Set3StateValue(checked ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    }
    void indeterminate()
    {
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->Set3StateValue(wxCHK_UNDETERMINED);
    }
    bool is_checked() const
    {
        wxCHECK_MSG(m_native, false, "Widget should be created");
        return m_native->Get3StateValue() == wxCHK_CHECKED;
    }
    bool is_unchecked() const
    {
        wxCHECK_MSG(m_native, false, "Widget should be created");
        return m_native->Get3StateValue() == wxCHK_UNCHECKED;
    }
    bool is_indeterminate() const
    {
        wxCHECK_MSG(m_native, false, "Widget should be created");
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
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->check(checked);
#endif

    return *this;
}

check_box_base& check_box_base::indeterminate()
{
#if wxUSE_CHECKBOX
    detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->indeterminate();
#endif

    return *this;
}

bool check_box_base::is_checked() const
{
#if wxUSE_CHECKBOX
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, false, "Widget should be created");

    return impl->is_checked();
#else
    return false;
#endif
}

bool check_box_base::is_unchecked() const
{
#if wxUSE_CHECKBOX
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, false, "Widget should be created");

    return impl->is_unchecked();
#else
    return false;
#endif
}

bool check_box_base::is_indeterminate() const
{
#if wxUSE_CHECKBOX
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, false, "Widget should be created");

    return impl->is_indeterminate();
#else
    return false;
#endif
}

void check_box_base::on_toggle_raw(const boost::function<void()>& handler)
{
#if wxUSE_CHECKBOX
    native::bind_helper(*this, wxEVT_CHECKBOX, handler);
#endif
}

} // namespace ui
} // namespace boost
