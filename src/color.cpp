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

const color color::aliceblue            = color::rgb255(240, 248, 255);
const color color::antiquewhite         = color::rgb255(250, 235, 215);
const color color::aqua                 = color::rgb255(0, 255, 255);
const color color::aquamarine           = color::rgb255(127, 255, 212);
const color color::azure                = color::rgb255(240, 255, 255);
const color color::beige                = color::rgb255(245, 245, 220);
const color color::bisque               = color::rgb255(255, 228, 196);
const color color::black                = color::rgb255(0, 0, 0);
const color color::blanchedalmond       = color::rgb255(255, 235, 205);
const color color::blue                 = color::rgb255(0, 0, 255);
const color color::blueviolet           = color::rgb255(138, 43, 226);
const color color::brown                = color::rgb255(165, 42, 42);
const color color::burlywood            = color::rgb255(222, 184, 135);
const color color::cadetblue            = color::rgb255(95, 158, 160);
const color color::chartreuse           = color::rgb255(127, 255, 0);
const color color::chocolate            = color::rgb255(210, 105, 30);
const color color::coral                = color::rgb255(255, 127, 80);
const color color::cornflowerblue       = color::rgb255(100, 149, 237);
const color color::cornsilk             = color::rgb255(255, 248, 220);
const color color::crimson              = color::rgb255(220, 20, 60);
const color color::cyan                 = color::rgb255(0, 255, 255);
const color color::darkblue             = color::rgb255(0, 0, 139);
const color color::darkcyan             = color::rgb255(0, 139, 139);
const color color::darkgoldenrod        = color::rgb255(184, 134, 11);
const color color::darkgray             = color::rgb255(169, 169, 169);
const color color::darkgreen            = color::rgb255(0, 100, 0);
const color color::darkgrey             = color::rgb255(169, 169, 169);
const color color::darkkhaki            = color::rgb255(189, 183, 107);
const color color::darkmagenta          = color::rgb255(139, 0, 139);
const color color::darkolivegreen       = color::rgb255(85, 107, 47);
const color color::darkorange           = color::rgb255(255, 140, 0);
const color color::darkorchid           = color::rgb255(153, 50, 204);
const color color::darkred              = color::rgb255(139, 0, 0);
const color color::darksalmon           = color::rgb255(233, 150, 122);
const color color::darkseagreen         = color::rgb255(143, 188, 143);
const color color::darkslateblue        = color::rgb255(72, 61, 139);
const color color::darkslategray        = color::rgb255(47, 79, 79);
const color color::darkslategrey        = color::rgb255(47, 79, 79);
const color color::darkturquoise        = color::rgb255(0, 206, 209);
const color color::darkviolet           = color::rgb255(148, 0, 211);
const color color::deeppink             = color::rgb255(255, 20, 147);
const color color::deepskyblue          = color::rgb255(0, 191, 255);
const color color::dimgray              = color::rgb255(105, 105, 105);
const color color::dimgrey              = color::rgb255(105, 105, 105);
const color color::dodgerblue           = color::rgb255(30, 144, 255);
const color color::firebrick            = color::rgb255(178, 34, 34);
const color color::floralwhite          = color::rgb255(255, 250, 240);
const color color::forestgreen          = color::rgb255(34, 139, 34);
const color color::fuchsia              = color::rgb255(255, 0, 255);
const color color::gainsboro            = color::rgb255(220, 220, 220);
const color color::ghostwhite           = color::rgb255(248, 248, 255);
const color color::gold                 = color::rgb255(255, 215, 0);
const color color::goldenrod            = color::rgb255(218, 165, 32);
const color color::gray                 = color::rgb255(128, 128, 128);
const color color::green                = color::rgb255(0, 128, 0);
const color color::greenyellow          = color::rgb255(173, 255, 47);
const color color::grey                 = color::rgb255(128, 128, 128);
const color color::honeydew             = color::rgb255(240, 255, 240);
const color color::hotpink              = color::rgb255(255, 105, 180);
const color color::indianred            = color::rgb255(205, 92, 92);
const color color::indigo               = color::rgb255(75, 0, 130);
const color color::ivory                = color::rgb255(255, 255, 240);
const color color::khaki                = color::rgb255(240, 230, 140);
const color color::lavender             = color::rgb255(230, 230, 250);
const color color::lavenderblush        = color::rgb255(255, 240, 245);
const color color::lawngreen            = color::rgb255(124, 252, 0);
const color color::lemonchiffon         = color::rgb255(255, 250, 205);
const color color::lightblue            = color::rgb255(173, 216, 230);
const color color::lightcoral           = color::rgb255(240, 128, 128);
const color color::lightcyan            = color::rgb255(224, 255, 255);
const color color::lightgoldenrodyellow = color::rgb255(250, 250, 210);
const color color::lightgray            = color::rgb255(211, 211, 211);
const color color::lightgreen           = color::rgb255(144, 238, 144);
const color color::lightgrey            = color::rgb255(211, 211, 211);
const color color::lightpink            = color::rgb255(255, 182, 193);
const color color::lightsalmon          = color::rgb255(255, 160, 122);
const color color::lightseagreen        = color::rgb255(32, 178, 170);
const color color::lightskyblue         = color::rgb255(135, 206, 250);
const color color::lightslategray       = color::rgb255(119, 136, 153);
const color color::lightslategrey       = color::rgb255(119, 136, 153);
const color color::lightsteelblue       = color::rgb255(176, 196, 222);
const color color::lightyellow          = color::rgb255(255, 255, 224);
const color color::lime                 = color::rgb255(0, 255, 0);
const color color::limegreen            = color::rgb255(50, 205, 50);
const color color::linen                = color::rgb255(250, 240, 230);
const color color::magenta              = color::rgb255(255, 0, 255);
const color color::maroon               = color::rgb255(128, 0, 0);
const color color::mediumaquamarine     = color::rgb255(102, 205, 170);
const color color::mediumblue           = color::rgb255(0, 0, 205);
const color color::mediumorchid         = color::rgb255(186, 85, 211);
const color color::mediumpurple         = color::rgb255(147, 112, 219);
const color color::mediumseagreen       = color::rgb255(60, 179, 113);
const color color::mediumslateblue      = color::rgb255(123, 104, 238);
const color color::mediumspringgreen    = color::rgb255(0, 250, 154);
const color color::mediumturquoise      = color::rgb255(72, 209, 204);
const color color::mediumvioletred      = color::rgb255(199, 21, 133);
const color color::midnightblue         = color::rgb255(25, 25, 112);
const color color::mintcream            = color::rgb255(245, 255, 250);
const color color::mistyrose            = color::rgb255(255, 228, 225);
const color color::moccasin             = color::rgb255(255, 228, 181);
const color color::navajowhite          = color::rgb255(255, 222, 173);
const color color::navy                 = color::rgb255(0, 0, 128);
const color color::oldlace              = color::rgb255(253, 245, 230);
const color color::olive                = color::rgb255(128, 128, 0);
const color color::olivedrab            = color::rgb255(107, 142, 35);
const color color::orange               = color::rgb255(255, 165, 0);
const color color::orangered            = color::rgb255(255, 69, 0);
const color color::orchid               = color::rgb255(218, 112, 214);
const color color::palegoldenrod        = color::rgb255(238, 232, 170);
const color color::palegreen            = color::rgb255(152, 251, 152);
const color color::paleturquoise        = color::rgb255(175, 238, 238);
const color color::palevioletred        = color::rgb255(219, 112, 147);
const color color::papayawhip           = color::rgb255(255, 239, 213);
const color color::peachpuff            = color::rgb255(255, 218, 185);
const color color::peru                 = color::rgb255(205, 133, 63);
const color color::pink                 = color::rgb255(255, 192, 203);
const color color::plum                 = color::rgb255(221, 160, 221);
const color color::powderblue           = color::rgb255(176, 224, 230);
const color color::purple               = color::rgb255(128, 0, 128);
const color color::red                  = color::rgb255(255, 0, 0);
const color color::rosybrown            = color::rgb255(188, 143, 143);
const color color::royalblue            = color::rgb255(65, 105, 225);
const color color::saddlebrown          = color::rgb255(139, 69, 19);
const color color::salmon               = color::rgb255(250, 128, 114);
const color color::sandybrown           = color::rgb255(244, 164, 96);
const color color::seagreen             = color::rgb255(46, 139, 87);
const color color::seashell             = color::rgb255(255, 245, 238);
const color color::sienna               = color::rgb255(160, 82, 45);
const color color::silver               = color::rgb255(192, 192, 192);
const color color::skyblue              = color::rgb255(135, 206, 235);
const color color::slateblue            = color::rgb255(106, 90, 205);
const color color::slategray            = color::rgb255(112, 128, 144);
const color color::slategrey            = color::rgb255(112, 128, 144);
const color color::snow                 = color::rgb255(255, 250, 250);
const color color::springgreen          = color::rgb255(0, 255, 127);
const color color::steelblue            = color::rgb255(70, 130, 180);
const color color::tan                  = color::rgb255(210, 180, 140);
const color color::teal                 = color::rgb255(0, 128, 128);
const color color::thistle              = color::rgb255(216, 191, 216);
const color color::tomato               = color::rgb255(255, 99, 71);
const color color::turquoise            = color::rgb255(64, 224, 208);
const color color::violet               = color::rgb255(238, 130, 238);
const color color::wheat                = color::rgb255(245, 222, 179);
const color color::white                = color::rgb255(255, 255, 255);
const color color::whitesmoke           = color::rgb255(245, 245, 245);
const color color::yellow               = color::rgb255(255, 255, 0);
const color color::yellowgreen          = color::rgb255(154, 205, 50);

} // namespace ui
} // namespace boost
