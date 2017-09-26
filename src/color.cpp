// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/color.hpp>

#include <boost/throw_exception.hpp>

#include <stdexcept>

namespace boost  {
namespace ui     {

color color::rgba255(channel255_type red, channel255_type green,
                     channel255_type blue, channel255_type alpha)
{
    if ( red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255 || alpha < 0 || alpha > 255 )
        BOOST_THROW_EXCEPTION(std::out_of_range("color value not in [0, 255] range"));
    color c;
    c.m_red   = red;
    c.m_green = green;
    c.m_blue  = blue;
    c.m_alpha = alpha;
    return c;
}

color color::rgba1(channel1_type red, channel1_type green,
                   channel1_type blue, channel1_type alpha)
{
    if ( red < 0 || red > 1 || green < 0 || green > 1 || blue < 0 || blue > 1 || alpha < 0 || alpha > 1 )
        BOOST_THROW_EXCEPTION(std::out_of_range("color value not in [0, 1] range"));

    color c;
    c.m_red   = static_cast<channel255_type>(red   * 255 + 0.5);
    c.m_green = static_cast<channel255_type>(green * 255 + 0.5);
    c.m_blue  = static_cast<channel255_type>(blue  * 255 + 0.5);
    c.m_alpha = static_cast<channel255_type>(alpha * 255 + 0.5);
    return c;
}

namespace colors {

const color& aliceblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(240, 248, 255);
    return c;
}

const color& antiquewhite() BOOST_NOEXCEPT
{
    static color c = color::rgb255(250, 235, 215);
    return c;
}

const color& aqua() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 255, 255);
    return c;
}

const color& aquamarine() BOOST_NOEXCEPT
{
    static color c = color::rgb255(127, 255, 212);
    return c;
}

const color& azure() BOOST_NOEXCEPT
{
    static color c = color::rgb255(240, 255, 255);
    return c;
}

const color& beige() BOOST_NOEXCEPT
{
    static color c = color::rgb255(245, 245, 220);
    return c;
}

const color& bisque() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 228, 196);
    return c;
}

const color& black() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 0, 0);
    return c;
}

const color& blanchedalmond() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 235, 205);
    return c;
}

const color& blue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 0, 255);
    return c;
}

const color& blueviolet() BOOST_NOEXCEPT
{
    static color c = color::rgb255(138, 43, 226);
    return c;
}

const color& brown() BOOST_NOEXCEPT
{
    static color c = color::rgb255(165, 42, 42);
    return c;
}

const color& burlywood() BOOST_NOEXCEPT
{
    static color c = color::rgb255(222, 184, 135);
    return c;
}

const color& cadetblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(95, 158, 160);
    return c;
}

const color& chartreuse() BOOST_NOEXCEPT
{
    static color c = color::rgb255(127, 255, 0);
    return c;
}

const color& chocolate() BOOST_NOEXCEPT
{
    static color c = color::rgb255(210, 105, 30);
    return c;
}

const color& coral() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 127, 80);
    return c;
}

const color& cornflowerblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(100, 149, 237);
    return c;
}

const color& cornsilk() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 248, 220);
    return c;
}

const color& crimson() BOOST_NOEXCEPT
{
    static color c = color::rgb255(220, 20, 60);
    return c;
}

const color& cyan() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 255, 255);
    return c;
}

const color& darkblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 0, 139);
    return c;
}

const color& darkcyan() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 139, 139);
    return c;
}

const color& darkgoldenrod() BOOST_NOEXCEPT
{
    static color c = color::rgb255(184, 134, 11);
    return c;
}

const color& darkgray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(169, 169, 169);
    return c;
}

const color& darkgreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 100, 0);
    return c;
}

const color& darkgrey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(169, 169, 169);
    return c;
}

const color& darkkhaki() BOOST_NOEXCEPT
{
    static color c = color::rgb255(189, 183, 107);
    return c;
}

const color& darkmagenta() BOOST_NOEXCEPT
{
    static color c = color::rgb255(139, 0, 139);
    return c;
}

const color& darkolivegreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(85, 107, 47);
    return c;
}

const color& darkorange() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 140, 0);
    return c;
}

const color& darkorchid() BOOST_NOEXCEPT
{
    static color c = color::rgb255(153, 50, 204);
    return c;
}

const color& darkred() BOOST_NOEXCEPT
{
    static color c = color::rgb255(139, 0, 0);
    return c;
}

const color& darksalmon() BOOST_NOEXCEPT
{
    static color c = color::rgb255(233, 150, 122);
    return c;
}

const color& darkseagreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(143, 188, 143);
    return c;
}

const color& darkslateblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(72, 61, 139);
    return c;
}

const color& darkslategray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(47, 79, 79);
    return c;
}

const color& darkslategrey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(47, 79, 79);
    return c;
}

const color& darkturquoise() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 206, 209);
    return c;
}

const color& darkviolet() BOOST_NOEXCEPT
{
    static color c = color::rgb255(148, 0, 211);
    return c;
}

const color& deeppink() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 20, 147);
    return c;
}

const color& deepskyblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 191, 255);
    return c;
}

const color& dimgray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(105, 105, 105);
    return c;
}

const color& dimgrey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(105, 105, 105);
    return c;
}

const color& dodgerblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(30, 144, 255);
    return c;
}

const color& firebrick() BOOST_NOEXCEPT
{
    static color c = color::rgb255(178, 34, 34);
    return c;
}

const color& floralwhite() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 250, 240);
    return c;
}

const color& forestgreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(34, 139, 34);
    return c;
}

const color& fuchsia() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 0, 255);
    return c;
}

const color& gainsboro() BOOST_NOEXCEPT
{
    static color c = color::rgb255(220, 220, 220);
    return c;
}

const color& ghostwhite() BOOST_NOEXCEPT
{
    static color c = color::rgb255(248, 248, 255);
    return c;
}

const color& gold() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 215, 0);
    return c;
}

const color& goldenrod() BOOST_NOEXCEPT
{
    static color c = color::rgb255(218, 165, 32);
    return c;
}

const color& gray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(128, 128, 128);
    return c;
}

const color& green() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 128, 0);
    return c;
}

const color& greenyellow() BOOST_NOEXCEPT
{
    static color c = color::rgb255(173, 255, 47);
    return c;
}

const color& grey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(128, 128, 128);
    return c;
}

const color& honeydew() BOOST_NOEXCEPT
{
    static color c = color::rgb255(240, 255, 240);
    return c;
}

const color& hotpink() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 105, 180);
    return c;
}

const color& indianred() BOOST_NOEXCEPT
{
    static color c = color::rgb255(205, 92, 92);
    return c;
}

const color& indigo() BOOST_NOEXCEPT
{
    static color c = color::rgb255(75, 0, 130);
    return c;
}

const color& ivory() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 255, 240);
    return c;
}

const color& khaki() BOOST_NOEXCEPT
{
    static color c = color::rgb255(240, 230, 140);
    return c;
}

const color& lavender() BOOST_NOEXCEPT
{
    static color c = color::rgb255(230, 230, 250);
    return c;
}

const color& lavenderblush() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 240, 245);
    return c;
}

const color& lawngreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(124, 252, 0);
    return c;
}

const color& lemonchiffon() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 250, 205);
    return c;
}

const color& lightblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(173, 216, 230);
    return c;
}

const color& lightcoral() BOOST_NOEXCEPT
{
    static color c = color::rgb255(240, 128, 128);
    return c;
}

const color& lightcyan() BOOST_NOEXCEPT
{
    static color c = color::rgb255(224, 255, 255);
    return c;
}

const color& lightgoldenrodyellow() BOOST_NOEXCEPT
{
    static color c = color::rgb255(250, 250, 210);
    return c;
}

const color& lightgray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(211, 211, 211);
    return c;
}

const color& lightgreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(144, 238, 144);
    return c;
}

const color& lightgrey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(211, 211, 211);
    return c;
}

const color& lightpink() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 182, 193);
    return c;
}

const color& lightsalmon() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 160, 122);
    return c;
}

const color& lightseagreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(32, 178, 170);
    return c;
}

const color& lightskyblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(135, 206, 250);
    return c;
}

const color& lightslategray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(119, 136, 153);
    return c;
}

const color& lightslategrey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(119, 136, 153);
    return c;
}

const color& lightsteelblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(176, 196, 222);
    return c;
}

const color& lightyellow() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 255, 224);
    return c;
}

const color& lime() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 255, 0);
    return c;
}

const color& limegreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(50, 205, 50);
    return c;
}

const color& linen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(250, 240, 230);
    return c;
}

const color& magenta() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 0, 255);
    return c;
}

const color& maroon() BOOST_NOEXCEPT
{
    static color c = color::rgb255(128, 0, 0);
    return c;
}

const color& mediumaquamarine() BOOST_NOEXCEPT
{
    static color c = color::rgb255(102, 205, 170);
    return c;
}

const color& mediumblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 0, 205);
    return c;
}

const color& mediumorchid() BOOST_NOEXCEPT
{
    static color c = color::rgb255(186, 85, 211);
    return c;
}

const color& mediumpurple() BOOST_NOEXCEPT
{
    static color c = color::rgb255(147, 112, 219);
    return c;
}

const color& mediumseagreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(60, 179, 113);
    return c;
}

const color& mediumslateblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(123, 104, 238);
    return c;
}

const color& mediumspringgreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 250, 154);
    return c;
}

const color& mediumturquoise() BOOST_NOEXCEPT
{
    static color c = color::rgb255(72, 209, 204);
    return c;
}

const color& mediumvioletred() BOOST_NOEXCEPT
{
    static color c = color::rgb255(199, 21, 133);
    return c;
}

const color& midnightblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(25, 25, 112);
    return c;
}

const color& mintcream() BOOST_NOEXCEPT
{
    static color c = color::rgb255(245, 255, 250);
    return c;
}

const color& mistyrose() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 228, 225);
    return c;
}

const color& moccasin() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 228, 181);
    return c;
}

const color& navajowhite() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 222, 173);
    return c;
}

const color& navy() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 0, 128);
    return c;
}

const color& oldlace() BOOST_NOEXCEPT
{
    static color c = color::rgb255(253, 245, 230);
    return c;
}

const color& olive() BOOST_NOEXCEPT
{
    static color c = color::rgb255(128, 128, 0);
    return c;
}

const color& olivedrab() BOOST_NOEXCEPT
{
    static color c = color::rgb255(107, 142, 35);
    return c;
}

const color& orange() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 165, 0);
    return c;
}

const color& orangered() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 69, 0);
    return c;
}

const color& orchid() BOOST_NOEXCEPT
{
    static color c = color::rgb255(218, 112, 214);
    return c;
}

const color& palegoldenrod() BOOST_NOEXCEPT
{
    static color c = color::rgb255(238, 232, 170);
    return c;
}

const color& palegreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(152, 251, 152);
    return c;
}

const color& paleturquoise() BOOST_NOEXCEPT
{
    static color c = color::rgb255(175, 238, 238);
    return c;
}

const color& palevioletred() BOOST_NOEXCEPT
{
    static color c = color::rgb255(219, 112, 147);
    return c;
}

const color& papayawhip() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 239, 213);
    return c;
}

const color& peachpuff() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 218, 185);
    return c;
}

const color& peru() BOOST_NOEXCEPT
{
    static color c = color::rgb255(205, 133, 63);
    return c;
}

const color& pink() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 192, 203);
    return c;
}

const color& plum() BOOST_NOEXCEPT
{
    static color c = color::rgb255(221, 160, 221);
    return c;
}

const color& powderblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(176, 224, 230);
    return c;
}

const color& purple() BOOST_NOEXCEPT
{
    static color c = color::rgb255(128, 0, 128);
    return c;
}

const color& red() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 0, 0);
    return c;
}

const color& rosybrown() BOOST_NOEXCEPT
{
    static color c = color::rgb255(188, 143, 143);
    return c;
}

const color& royalblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(65, 105, 225);
    return c;
}

const color& saddlebrown() BOOST_NOEXCEPT
{
    static color c = color::rgb255(139, 69, 19);
    return c;
}

const color& salmon() BOOST_NOEXCEPT
{
    static color c = color::rgb255(250, 128, 114);
    return c;
}

const color& sandybrown() BOOST_NOEXCEPT
{
    static color c = color::rgb255(244, 164, 96);
    return c;
}

const color& seagreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(46, 139, 87);
    return c;
}

const color& seashell() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 245, 238);
    return c;
}

const color& sienna() BOOST_NOEXCEPT
{
    static color c = color::rgb255(160, 82, 45);
    return c;
}

const color& silver() BOOST_NOEXCEPT
{
    static color c = color::rgb255(192, 192, 192);
    return c;
}

const color& skyblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(135, 206, 235);
    return c;
}

const color& slateblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(106, 90, 205);
    return c;
}

const color& slategray() BOOST_NOEXCEPT
{
    static color c = color::rgb255(112, 128, 144);
    return c;
}

const color& slategrey() BOOST_NOEXCEPT
{
    static color c = color::rgb255(112, 128, 144);
    return c;
}

const color& snow() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 250, 250);
    return c;
}

const color& springgreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 255, 127);
    return c;
}

const color& steelblue() BOOST_NOEXCEPT
{
    static color c = color::rgb255(70, 130, 180);
    return c;
}

const color& tan() BOOST_NOEXCEPT
{
    static color c = color::rgb255(210, 180, 140);
    return c;
}

const color& teal() BOOST_NOEXCEPT
{
    static color c = color::rgb255(0, 128, 128);
    return c;
}

const color& thistle() BOOST_NOEXCEPT
{
    static color c = color::rgb255(216, 191, 216);
    return c;
}

const color& tomato() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 99, 71);
    return c;
}

const color& turquoise() BOOST_NOEXCEPT
{
    static color c = color::rgb255(64, 224, 208);
    return c;
}

const color& violet() BOOST_NOEXCEPT
{
    static color c = color::rgb255(238, 130, 238);
    return c;
}

const color& wheat() BOOST_NOEXCEPT
{
    static color c = color::rgb255(245, 222, 179);
    return c;
}

const color& white() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 255, 255);
    return c;
}

const color& whitesmoke() BOOST_NOEXCEPT
{
    static color c = color::rgb255(245, 245, 245);
    return c;
}

const color& yellow() BOOST_NOEXCEPT
{
    static color c = color::rgb255(255, 255, 0);
    return c;
}

const color& yellowgreen() BOOST_NOEXCEPT
{
    static color c = color::rgb255(154, 205, 50);
    return c;
}

} // namespace colors
} // namespace ui
} // namespace boost
