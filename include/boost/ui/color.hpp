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
    static const color aliceblue;
    static const color antiquewhite;
    static const color aqua;
    static const color aquamarine;
    static const color azure;
    static const color beige;
    static const color bisque;
    static const color black;
    static const color blanchedalmond;
    static const color blue;
    static const color blueviolet;
    static const color brown;
    static const color burlywood;
    static const color cadetblue;
    static const color chartreuse;
    static const color chocolate;
    static const color coral;
    static const color cornflowerblue;
    static const color cornsilk;
    static const color crimson;
    static const color cyan;
    static const color darkblue;
    static const color darkcyan;
    static const color darkgoldenrod;
    static const color darkgray;
    static const color darkgreen;
    static const color darkgrey;
    static const color darkkhaki;
    static const color darkmagenta;
    static const color darkolivegreen;
    static const color darkorange;
    static const color darkorchid;
    static const color darkred;
    static const color darksalmon;
    static const color darkseagreen;
    static const color darkslateblue;
    static const color darkslategray;
    static const color darkslategrey;
    static const color darkturquoise;
    static const color darkviolet;
    static const color deeppink;
    static const color deepskyblue;
    static const color dimgray;
    static const color dimgrey;
    static const color dodgerblue;
    static const color firebrick;
    static const color floralwhite;
    static const color forestgreen;
    static const color fuchsia;
    static const color gainsboro;
    static const color ghostwhite;
    static const color gold;
    static const color goldenrod;
    static const color gray;
    static const color green;
    static const color greenyellow;
    static const color grey;
    static const color honeydew;
    static const color hotpink;
    static const color indianred;
    static const color indigo;
    static const color ivory;
    static const color khaki;
    static const color lavender;
    static const color lavenderblush;
    static const color lawngreen;
    static const color lemonchiffon;
    static const color lightblue;
    static const color lightcoral;
    static const color lightcyan;
    static const color lightgoldenrodyellow;
    static const color lightgray;
    static const color lightgreen;
    static const color lightgrey;
    static const color lightpink;
    static const color lightsalmon;
    static const color lightseagreen;
    static const color lightskyblue;
    static const color lightslategray;
    static const color lightslategrey;
    static const color lightsteelblue;
    static const color lightyellow;
    static const color lime;
    static const color limegreen;
    static const color linen;
    static const color magenta;
    static const color maroon;
    static const color mediumaquamarine;
    static const color mediumblue;
    static const color mediumorchid;
    static const color mediumpurple;
    static const color mediumseagreen;
    static const color mediumslateblue;
    static const color mediumspringgreen;
    static const color mediumturquoise;
    static const color mediumvioletred;
    static const color midnightblue;
    static const color mintcream;
    static const color mistyrose;
    static const color moccasin;
    static const color navajowhite;
    static const color navy;
    static const color oldlace;
    static const color olive;
    static const color olivedrab;
    static const color orange;
    static const color orangered;
    static const color orchid;
    static const color palegoldenrod;
    static const color palegreen;
    static const color paleturquoise;
    static const color palevioletred;
    static const color papayawhip;
    static const color peachpuff;
    static const color peru;
    static const color pink;
    static const color plum;
    static const color powderblue;
    static const color purple;
    static const color red;
    static const color rosybrown;
    static const color royalblue;
    static const color saddlebrown;
    static const color salmon;
    static const color sandybrown;
    static const color seagreen;
    static const color seashell;
    static const color sienna;
    static const color silver;
    static const color skyblue;
    static const color slateblue;
    static const color slategray;
    static const color slategrey;
    static const color snow;
    static const color springgreen;
    static const color steelblue;
    static const color tan;
    static const color teal;
    static const color thistle;
    static const color tomato;
    static const color turquoise;
    static const color violet;
    static const color wheat;
    static const color white;
    static const color whitesmoke;
    static const color yellow;
    static const color yellowgreen;
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
