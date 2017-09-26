// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file color.hpp Color class

#ifndef BOOST_UI_COLOR_HPP
#define BOOST_UI_COLOR_HPP

#include <boost/ui/config.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace ui    {

/// @brief Color class
/// @see boost::ui::colors predefined colors namespace
/// @see <a href="http://www.w3.org/TR/css3-color/">CSS Color Module (W3C)</a>
/// @see <a href="http://en.wikipedia.org/wiki/Color">Color (Wikipedia)</a>
/// @see <a href="http://en.wikipedia.org/wiki/RGB_color_model">RGB color model (Wikipedia)</a>
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

/// @brief Predefined colors
/// @see <a href="http://www.w3.org/TR/css3-color/#html4">Basic CSS colors (W3C)</a>
/// @see <a href="http://www.w3.org/TR/css3-color/#svg-color">Extended CSS colors (W3C)</a>
/// @see <a href="https://en.wikipedia.org/wiki/Web_colors">Web colors (Wikipedia)</a>
/// @ingroup graphics
namespace colors
{
///@{ Predefined color
extern BOOST_UI_DECL const color& aliceblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& antiquewhite() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& aqua() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& aquamarine() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& azure() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& beige() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& bisque() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& black() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& blanchedalmond() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& blue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& blueviolet() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& brown() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& burlywood() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& cadetblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& chartreuse() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& chocolate() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& coral() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& cornflowerblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& cornsilk() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& crimson() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& cyan() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkcyan() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkgoldenrod() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkgray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkgreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkgrey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkkhaki() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkmagenta() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkolivegreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkorange() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkorchid() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkred() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darksalmon() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkseagreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkslateblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkslategray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkslategrey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkturquoise() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& darkviolet() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& deeppink() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& deepskyblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& dimgray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& dimgrey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& dodgerblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& firebrick() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& floralwhite() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& forestgreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& fuchsia() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& gainsboro() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& ghostwhite() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& gold() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& goldenrod() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& gray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& green() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& greenyellow() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& grey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& honeydew() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& hotpink() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& indianred() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& indigo() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& ivory() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& khaki() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lavender() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lavenderblush() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lawngreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lemonchiffon() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightcoral() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightcyan() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightgoldenrodyellow() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightgray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightgreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightgrey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightpink() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightsalmon() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightseagreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightskyblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightslategray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightslategrey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightsteelblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lightyellow() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& lime() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& limegreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& linen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& magenta() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& maroon() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumaquamarine() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumorchid() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumpurple() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumseagreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumslateblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumspringgreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumturquoise() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mediumvioletred() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& midnightblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mintcream() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& mistyrose() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& moccasin() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& navajowhite() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& navy() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& oldlace() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& olive() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& olivedrab() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& orange() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& orangered() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& orchid() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& palegoldenrod() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& palegreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& paleturquoise() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& palevioletred() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& papayawhip() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& peachpuff() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& peru() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& pink() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& plum() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& powderblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& purple() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& red() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& rosybrown() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& royalblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& saddlebrown() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& salmon() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& sandybrown() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& seagreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& seashell() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& sienna() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& silver() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& skyblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& slateblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& slategray() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& slategrey() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& snow() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& springgreen() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& steelblue() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& tan() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& teal() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& thistle() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& tomato() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& turquoise() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& violet() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& wheat() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& white() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& whitesmoke() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& yellow() BOOST_NOEXCEPT;
extern BOOST_UI_DECL const color& yellowgreen() BOOST_NOEXCEPT;
///@}
} // namespace colors

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COLOR_HPP
