// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_IMAGE_HPP
#define BOOST_UI_NATIVE_IMAGE_HPP

class wxBitmap;

#include <boost/ui/image.hpp>

namespace boost  {
namespace ui     {
namespace native {

inline wxBitmap* from_image_ptr(ui::image& img)
{
    return static_cast<wxBitmap*>(img.native_handle());
}

inline const wxBitmap* from_image_ptr(const ui::image& img)
{
    return static_cast<const wxBitmap*>(img.native_handle());
}

} // namespace native
} // namespace ui
} // namespace boost

#endif // BOOST_UI_NATIVE_IMAGE_HPP
