// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/stringsbox.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/ctrlsub.h>

namespace boost {
namespace ui    {

#if wxUSE_CONTROLS

class stringsbox::native_impl : public wxControlWithItems, private detail::memcheck
{
};

#endif

stringsbox::native_impl* stringsbox::get_native()
{
#if wxUSE_CONTROLS
    return native::impl<native_impl, wxControlWithItems>(*this);
#else
    return NULL;
#endif
}

const stringsbox::native_impl* stringsbox::get_native() const
{
#if wxUSE_CONTROLS
    return native::impl<native_impl, wxControlWithItems>(*this);
#else
    return NULL;
#endif
}

uistring stringsbox::at(size_type pos) const
{
    check_range(pos);
    return operator[](pos);
}

uistring stringsbox::operator[](size_type pos) const
{
#if wxUSE_CONTROLS
    const native_impl* impl = get_native();
    wxCHECK(impl, uistring());

    return native::to_uistring(impl->GetString(pos));
#else
    return uistring();
#endif
}

stringsbox::size_type stringsbox::size() const
{
#if wxUSE_CONTROLS
    const native_impl* impl = get_native();
    wxCHECK(impl, 0);

    return impl->GetCount();
#else
    return 0;
#endif
}

void stringsbox::clear()
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK(impl, );

    impl->Clear();
#endif
}

stringsbox& stringsbox::append(const std::vector<uistring>& options)
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK(impl, *this);

    impl->Set(native::from_vector_uistring(options));
#endif

    return *this;
}

void stringsbox::push_back(const uistring& value)
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK(impl, );

    impl->Append(native::from_uistring(value));
#endif
}

stringsbox& stringsbox::select(size_type pos)
{
#if wxUSE_CONTROLS
    native_impl* impl = get_native();
    wxCHECK(impl, *this);

    impl->Select(pos);
#endif

    return *this;
}

void stringsbox::check_range(size_type pos) const
{
    if ( pos < 0 || pos >= size() )
        BOOST_THROW_EXCEPTION(std::out_of_range("ui::stringsbox::check_range(): invalid index"));
}

} // namespace ui
} // namespace boost
