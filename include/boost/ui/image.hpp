// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file image.hpp Image class

#ifndef BOOST_UI_IMAGE_HPP
#define BOOST_UI_IMAGE_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/coord.hpp>

#include <istream>

namespace boost {
namespace ui    {

/// @brief Image class
/// @see <a href="https://en.wikipedia.org/wiki/Digital_image">Digital image (Wikipedia)</a>
/// @ingroup graphics

class BOOST_UI_DECL image
{
    class impl;

public:
    image();
#ifndef DOXYGEN
    image(const image& other);
    image& operator=(const image& other);
#endif
    ~image();

    /// @brief Loads image from the stream
    /// @throw std::runtime_error On image load failure
    /// @see <a href="https://en.wikipedia.org/wiki/Image_file_formats">Image file formats (Wikipedia)</a>
    image& load(std::istream& s);

    /// @brief Returns standard freedesktop.org (XDG) icon by name
    /// @see <a href="https://specifications.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html#names">
    /// freedesktop.org Icon Naming Specification</a>
    static image xdg(const char* name, coord_type width, coord_type height);

    /// @brief Returns image width
    /// @throw std::runtime_error On invalid image
    coord_type width() const;

    /// @brief Returns image height
    /// @throw std::runtime_error On invalid image
    coord_type height() const;

    /// @brief Returns image size
    /// @throw std::runtime_error On invalid image
    size dimensions() const
        { return size(width(), height()); }

    /// Returns true only if image is valid
    bool valid() const BOOST_NOEXCEPT;

    /// Implementation-defined image type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying image handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    impl* m_impl;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_IMAGE_HPP
