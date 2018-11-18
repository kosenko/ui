// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/notebook.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/notebook.h>

namespace boost {
namespace ui    {

#if wxUSE_NOTEBOOK

class notebook::detail_impl : public detail::widget_detail<wxNotebook>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(new wxNotebook(native::from_widget(parent),
            wxID_ANY));
    }
    void append_page(widget& page, const uistring& label)
    {
        wxWindow* page_window = native::from_widget(page);
        wxCHECK_RET(page_window, "Page widget should be created");

        wxCHECK_RET(m_native, "Widget should be created");
        m_native->AddPage(page_window, native::from_uistring(label));
    }
    void set_current_page(size_type index)
    {
        wxCHECK_RET(m_native, "Widget should be created");
        m_native->ChangeSelection(index);
    }
    size_type current_page_index() const
    {
        wxCHECK_MSG(m_native, npos, "Widget should be created");
        return m_native->GetSelection();
    }
};

#endif

notebook::detail_impl* notebook::get_impl()
{
#if wxUSE_NOTEBOOK
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const notebook::detail_impl* notebook::get_impl() const
{
#if wxUSE_NOTEBOOK
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

notebook& notebook::create(widget& parent)
{
#if wxUSE_NOTEBOOK
    detail_set_detail_impl(new detail_impl(parent));
#endif

    return *this;
}

void notebook::append_page(widget& page, const uistring& label)
{
#if wxUSE_NOTEBOOK
    detail_impl* impl = get_impl();
    wxCHECK_RET(impl, "Widget should be created");

    impl->append_page(page, label);
#endif
}

void notebook::current_page(size_type index)
{
#if wxUSE_NOTEBOOK
    detail_impl* impl = get_impl();
    wxCHECK_RET(impl, "Widget should be created");

    impl->set_current_page(index);
#endif
}

notebook::size_type notebook::current_page_index() const
{
#if wxUSE_NOTEBOOK
    const detail_impl* impl = get_impl();
    wxCHECK_MSG(impl, npos, "Widget should be created");

    return impl->current_page_index();
#else
    return npos;
#endif
}

} // namespace ui
} // namespace boost
