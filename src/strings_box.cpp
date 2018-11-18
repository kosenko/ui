// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/strings_box.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/ctrlsub.h>

namespace boost {
namespace ui    {

#if wxUSE_CONTROLS

class strings_box::native_impl : public wxControlWithItems, private detail::memcheck
{
};

#endif

strings_box::native_impl* strings_box::get_native()
{
#if wxUSE_CONTROLS
    return native::impl<native_impl, wxControlWithItems>(*this);
#else
    return NULL;
#endif
}

const strings_box::native_impl* strings_box::get_native() const
{
#if wxUSE_CONTROLS
    return native::impl<native_impl, wxControlWithItems>(*this);
#else
    return NULL;
#endif
}

uistring strings_box::at(size_type pos) const
{
    check_range(pos);
    return operator[](pos);
}

uistring strings_box::operator[](size_type pos) const
{
#if wxUSE_CONTROLS
    const native_impl* impl = get_native();
    wxCHECK_MSG(impl, uistring(), "Widget should be created");

    return native::to_uistring(impl->GetString(pos));
#else
    return uistring();
#endif
}

strings_box::size_type strings_box::size() const
{
#if wxUSE_CONTROLS
    const native_impl* impl = get_native();
    wxCHECK_MSG(impl, 0, "Widget should be created");

    return impl->GetCount();
#else
    return 0;
#endif
}

void strings_box::clear()
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK_RET(impl, "Widget should be created");

    impl->Clear();
#endif
}

strings_box& strings_box::append(const std::vector<uistring>& options)
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->Set(native::from_vector_uistring(options));
#endif

    return *this;
}

void strings_box::push_back(const uistring& value)
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK_RET(impl, "Widget should be created");

    impl->Append(native::from_uistring(value));
#endif
}

strings_box& strings_box::select(size_type pos)
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK_MSG(impl, *this, "Widget should be created");

    impl->Select(pos);
#endif

    return *this;
}

void strings_box::check_range(size_type pos) const
{
    if ( pos < 0 || pos >= size() )
        BOOST_THROW_EXCEPTION(std::out_of_range("ui::strings_box::check_range(): invalid index"));
}

} // namespace ui
} // namespace boost
