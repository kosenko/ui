// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file font.hpp Font class

#ifndef BOOST_UI_FONT_HPP
#define BOOST_UI_FONT_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/string.hpp>

#include <boost/core/scoped_enum.hpp>

namespace boost {
namespace ui    {

/// @brief Font class
/// @see <a href="https://www.w3.org/TR/CSS2/fonts.html">CSS 2 Fonts (W3C)</a>
/// @see <a href="https://www.w3.org/TR/css-fonts-3/">CSS Fonts 3 (W3C)</a>
/// @see <a href="http://en.wikipedia.org/wiki/Font">Font (Wikipedia)</a>
/// @ingroup graphics

class BOOST_UI_DECL font
{
    class impl;

public:
    /// @brief Enumaration of font families
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(family)
    {
        other,      ///< Font family not listed here
        serif,      ///< Serif font family
        sans_serif, ///< Sans-serif font family
        cursive,    ///< Curisive font family
        fantasy,    ///< Decorative font family
        monospace   ///< Font family that all glyphs have the same fixed width
    }
    BOOST_SCOPED_ENUM_DECLARE_END(family)

    /// @brief Enumaration of font slants
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(slant)
    {
        normal, ///< Normal slant
        italic, ///< Italic slant
        oblique ///< Oblique slant
    }
    BOOST_SCOPED_ENUM_DECLARE_END(slant)

    /// @brief Enumaration of font weights
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(weight)
    {
        normal, ///< Normal weight
        bold    ///< Bold weight
    }
    BOOST_SCOPED_ENUM_DECLARE_END(weight)

    font();
#ifndef DOXYGEN
    font(const font& other);
    font& operator=(const font& other);
#endif
    ~font();

    ///@{ @brief Creates font
    explicit font(double pt, family f,
                  slant s = slant::normal, weight w = weight::normal);
    explicit font(double pt, const uistring& n,
                  slant s = slant::normal, weight w = weight::normal);
    ///@}

    /// @brief Sets font family
    font& set_family(family f);

    /// @brief Returns font family
    family get_family() const;

    /// @brief Sets font slant
    font& set_slant(slant s);

    /// @brief Returns font slant
    slant get_slant() const;

    /// @brief Sets font weight
    font& set_weight(weight w);

    /// @brief Returns font weight
    weight get_weight() const;

    /// @brief Sets font name
    /// @throw std::out_of_range If font name isn't supported
    font& name(const uistring& n);

    /// @brief Returns font name
    uistring name() const;

    /// @brief Sets font size in points
    /// @throw std::out_of_range If font size isn't positive value
    font& size_pt(double pt);

    /// @brief Returns font size in points
    double size_pt() const;

    /// Returns true only if font is valid
    bool valid() const BOOST_NOEXCEPT;

    /// Implementation-defined font type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying font handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

    /// @brief Returns default font used for captioned widgets
    static font caption() BOOST_NOEXCEPT;

private:
    impl* m_impl;

#ifndef DOXYGEN
    friend class native_helper;
#endif
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_FONT_HPP
