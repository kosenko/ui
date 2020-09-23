// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file color.hpp @brief Color class

#ifndef BOOST_UI_COLOR_HPP
#define BOOST_UI_COLOR_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/cstdint.hpp>

namespace boost {
namespace ui    {

/// @brief Color class
/// @see <a href="http://www.w3.org/TR/css3-color/">CSS Color Module (W3C)</a>
/// @see <a href="http://en.wikipedia.org/wiki/Color">Color (Wikipedia)</a>
/// @see <a href="http://en.wikipedia.org/wiki/RGB_color_model">RGB color model (Wikipedia)</a>
/// @see <a href="http://www.w3.org/TR/css3-color/#html4">Basic CSS colors (W3C)</a>
/// @see <a href="http://www.w3.org/TR/css3-color/#svg-color">Extended CSS colors (W3C)</a>
/// @see <a href="https://en.wikipedia.org/wiki/Web_colors">Web colors (Wikipedia)</a>
/// @ingroup graphics

class BOOST_UI_DECL color
{
public:
    /// @brief Create transparent black color
    color() BOOST_NOEXCEPT : m_red(0), m_green(0), m_blue(0), m_alpha(0) {}

    /// @brief Channel type with values in [0, 255] range
    typedef boost::uint_least8_t channel255_type;

    /// @brief Creates color from channels in [0, 255]
    static color rgba255(channel255_type red, channel255_type green,
                         channel255_type blue, channel255_type alpha);

    /// @brief Creates opaque color from channels in [0, 255] ragne
    /// @throw std::out_of_range
    static color rgb255(channel255_type red, channel255_type green, channel255_type blue)
        { return rgba255(red, green, blue, 255); }

    ///@{ @brief Returns color value in [0, 255] range
    channel255_type   red255() const BOOST_NOEXCEPT { return m_red;   }
    channel255_type green255() const BOOST_NOEXCEPT { return m_green; }
    channel255_type  blue255() const BOOST_NOEXCEPT { return m_blue;  }
    channel255_type alpha255() const BOOST_NOEXCEPT { return m_alpha; }
    ///@}

    /// @brief Channel type with values in [0, 1] range
    typedef double channel1_type;

    /// @brief Creates color from channels in [0, 1]
    /// @throw std::out_of_range
    static color rgba1(channel1_type red, channel1_type green,
                       channel1_type blue, channel1_type alpha);

    /// @brief Creates opaque color from channels in [0, 1] ragne
    static color rgb1(channel1_type red, channel1_type green, channel1_type blue)
        { return rgba1(red, green, blue, 1); }

    ///@{ @brief Returns color value in [0, 1] range
    channel1_type   red1() const BOOST_NOEXCEPT { return static_cast<channel1_type>(m_red)   / 255; }
    channel1_type green1() const BOOST_NOEXCEPT { return static_cast<channel1_type>(m_green) / 255; }
    channel1_type  blue1() const BOOST_NOEXCEPT { return static_cast<channel1_type>(m_blue)  / 255; }
    channel1_type alpha1() const BOOST_NOEXCEPT { return static_cast<channel1_type>(m_alpha) / 255; }
    ///@}

    ///@{ @brief Predefined color
    static const color alice_blue;
    static const color antique_white;
    static const color aqua;
    static const color aquamarine;
    static const color azure;
    static const color beige;
    static const color bisque;
    static const color black;
    static const color blanched_almond;
    static const color blue;
    static const color blue_violet;
    static const color brown;
    static const color burly_wood;
    static const color cadet_blue;
    static const color chartreuse;
    static const color chocolate;
    static const color coral;
    static const color cornflower_blue;
    static const color cornsilk;
    static const color crimson;
    static const color cyan;
    static const color dark_blue;
    static const color dark_cyan;
    static const color dark_goldenrod;
    static const color dark_gray;
    static const color dark_green;
    static const color dark_grey;
    static const color dark_khaki;
    static const color dark_magenta;
    static const color dark_olive_green;
    static const color dark_orange;
    static const color dark_orchid;
    static const color dark_red;
    static const color dark_salmon;
    static const color dark_sea_green;
    static const color dark_slate_blue;
    static const color dark_slate_gray;
    static const color dark_slate_grey;
    static const color dark_turquoise;
    static const color dark_violet;
    static const color deep_pink;
    static const color deep_sky_blue;
    static const color dim_gray;
    static const color dim_grey;
    static const color dodger_blue;
    static const color firebrick;
    static const color floral_white;
    static const color forest_green;
    static const color fuchsia;
    static const color gainsboro;
    static const color ghost_white;
    static const color gold;
    static const color goldenrod;
    static const color gray;
    static const color green;
    static const color green_yellow;
    static const color grey;
    static const color honeydew;
    static const color hot_pink;
    static const color indian_red;
    static const color indigo;
    static const color ivory;
    static const color khaki;
    static const color lavender;
    static const color lavender_blush;
    static const color lawn_green;
    static const color lemon_chiffon;
    static const color light_blue;
    static const color light_coral;
    static const color light_cyan;
    static const color light_goldenrod_yellow;
    static const color light_gray;
    static const color light_green;
    static const color light_grey;
    static const color light_pink;
    static const color light_salmon;
    static const color light_sea_green;
    static const color light_sky_blue;
    static const color light_slate_gray;
    static const color light_slate_grey;
    static const color light_steel_blue;
    static const color light_yellow;
    static const color lime;
    static const color lime_green;
    static const color linen;
    static const color magenta;
    static const color maroon;
    static const color medium_aquamarine;
    static const color medium_blue;
    static const color medium_orchid;
    static const color medium_purple;
    static const color medium_sea_green;
    static const color medium_slate_blue;
    static const color medium_spring_green;
    static const color medium_turquoise;
    static const color medium_violet_red;
    static const color midnight_blue;
    static const color mint_cream;
    static const color misty_rose;
    static const color moccasin;
    static const color navajo_white;
    static const color navy;
    static const color old_lace;
    static const color olive;
    static const color olive_drab;
    static const color orange;
    static const color orange_red;
    static const color orchid;
    static const color pale_goldenrod;
    static const color pale_green;
    static const color pale_turquoise;
    static const color pale_violet_red;
    static const color papaya_whip;
    static const color peach_puff;
    static const color peru;
    static const color pink;
    static const color plum;
    static const color powder_blue;
    static const color purple;
    static const color red;
    static const color rosy_brown;
    static const color royal_blue;
    static const color saddle_brown;
    static const color salmon;
    static const color sandy_brown;
    static const color sea_green;
    static const color sea_shell;
    static const color sienna;
    static const color silver;
    static const color sky_blue;
    static const color slate_blue;
    static const color slate_gray;
    static const color slate_grey;
    static const color snow;
    static const color spring_green;
    static const color steel_blue;
    static const color tan;
    static const color teal;
    static const color thistle;
    static const color tomato;
    static const color turquoise;
    static const color violet;
    static const color wheat;
    static const color white;
    static const color white_smoke;
    static const color yellow;
    static const color yellow_green;
    ///@}

private:
    channel255_type m_red;
    channel255_type m_green;
    channel255_type m_blue;
    channel255_type m_alpha;
};

///@{ @brief Compares two colors
///   @relatesalso boost::ui::color
inline bool operator==(const color& lhs, const color& rhs) BOOST_NOEXCEPT
{
    return lhs.red255()  == rhs.red255()  && lhs.green255() == rhs.green255() &&
           lhs.blue255() == rhs.blue255() && lhs.alpha255() == rhs.alpha255();
}
inline bool operator!=(const color& lhs, const color& rhs) BOOST_NOEXCEPT
    { return !operator==(lhs, rhs); }
///@}

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COLOR_HPP
