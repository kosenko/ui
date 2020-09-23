// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file painter.hpp @brief Painter class

#ifndef BOOST_UI_PAINTER_HPP
#define BOOST_UI_PAINTER_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/def.hpp>
#include <boost/ui/color.hpp>
#include <boost/ui/image.hpp>
#include <boost/ui/font.hpp>
#include <boost/ui/string.hpp>

#include <boost/noncopyable.hpp>
#include <boost/core/scoped_enum.hpp>

#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

namespace boost {
namespace ui    {

#ifndef DOXYGEN

namespace detail {
class painter_impl;
} // namespace detail

#endif

/// @brief Enumaration of line endings types
/// @ingroup graphics
BOOST_SCOPED_ENUM_DECLARE_BEGIN(line_cap)
{
    butt,  ///< no additional line cap is added
    round, ///< semi-circle with the diameter equal to the line width is added
    square ///< rectangle with the length equal to the line width
           ///< and width equal to the half of line width is added
}
BOOST_SCOPED_ENUM_DECLARE_END(line_cap)

/// @brief Enumaration of line join types
/// @ingroup graphics
BOOST_SCOPED_ENUM_DECLARE_BEGIN(line_join)
{
    round, ///< join with filled arc
    bevel, ///< no additional join drawings
    miter  ///< join with filled triangle
}
BOOST_SCOPED_ENUM_DECLARE_END(line_join)

/// @brief 2D graphics rendering painter
/// @see <a href="http://en.wikipedia.org/wiki/2D_computer_graphics">2D computer graphics (Wikipedia)</a>
/// @see <a href="http://www.w3.org/TR/2dcontext/">HTML Canvas 2D Context, Level 1 (W3C)</a>
/// @see <a href="http://www.w3.org/TR/2dcontext2/">HTML Canvas 2D Context, Level 2 (W3C)</a>
/// @ingroup graphics

class BOOST_UI_DECL painter
{
    painter(detail::painter_impl* impl);

public:
    /// Graphics coordinates signed number type
    typedef double gcoord_type;

    /// Push state
    painter& save()
        { save_raw(); return *this; }

    /// Pop state
    painter& restore()
        { restore_raw(); return *this; }

    /// Adds scaling transformation
    painter& scale(gcoord_type x, gcoord_type y)
        { scale_raw(x, y); return *this; }

    /// Adds rotation transformation
    painter& rotate(gcoord_type angle)
        { rotate_raw(angle); return *this; }

    ///@{ Adds translation transformation
    painter& translate(gcoord_type x, gcoord_type y)
        { translate_raw(x, y); return *this; }

    template <class T>
    painter& translate(const basic_point<T>& p)
        { return translate(p.x(), p.y()); }
    ///@}

    /// Sets the current color used for filling shapes
    painter& fill_color(const color& c)
        { fill_color_raw(c); return *this; }

    /// Sets the current color used for filling shapes
    painter& stroke_color(const color& c)
        { stroke_color_raw(c); return *this; }

    ///@{ Clears all pixels on the painter in the given rectangle to transparent black
    painter& clear_rect(gcoord_type x, gcoord_type y, gcoord_type width, gcoord_type height)
        { clear_rect_raw(x, y, width, height); return *this; }

    template <class T>
    painter& clear_rect(const basic_rect<T>& r)
        { return clear_rect(r.x(), r.y(), r.width(), r.height()); }

    template <class T>
    painter& clear_rect(const basic_point<T>& point, const basic_size<T>& size)
        { return clear_rect(point.x(), point.y(), size.width(), size.height()); }

    template <class T>
    painter& clear_rect(const basic_point<T>& point1, const basic_point<T>& point2)
        { return clear_rect(point1.x(), point1.y(), point2.x() - point1.x(), point2.y() - point1.y()); }
    ///@}

    ///@{ Paints the given rectangle onto the painter, using the current fill style
    painter& fill_rect(gcoord_type x, gcoord_type y, gcoord_type width, gcoord_type height)
        { fill_rect_raw(x, y, width, height); return *this; }

    template <class T>
    painter& fill_rect(const basic_rect<T>& r)
        { return fill_rect(r.x(), r.y(), r.width(), r.height()); }

    template <class T>
    painter& fill_rect(const basic_point<T>& point, const basic_size<T>& size)
        { return fill_rect(point.x(), point.y(), size.width(), size.height()); }

    template <class T>
    painter& fill_rect(const basic_point<T>& point1, const basic_point<T>& point2)
        { return fill_rect(point1.x(), point1.y(), point2.x() - point1.x(), point2.y() - point1.y()); }
    ///@}

    ///@{ Paints the box that outlines the given rectangle onto the painter, using the current stroke style
    painter& stroke_rect(gcoord_type x, gcoord_type y, gcoord_type width, gcoord_type height)
        { stroke_rect_raw(x, y, width, height); return *this; }

    template <class T>
    painter& stroke_rect(const basic_rect<T>& r)
        { return stroke_rect(r.x(), r.y(), r.width(), r.height()); }

    template <class T>
    painter& stroke_rect(const basic_point<T>& point, const basic_size<T>& size)
        { return stroke_rect(point.x(), point.y(), size.width(), size.height()); }

    template <class T>
    painter& stroke_rect(const basic_point<T>& point1, const basic_point<T>& point2)
        { return stroke_rect(point1.x(), point1.y(), point2.x() - point1.x(), point2.y() - point1.y()); }
    ///@}

    ///@{ Fills the given text at the given position
    painter& fill_text(const uistring& text, gcoord_type x, gcoord_type y)
        { fill_text_raw(text, x, y); return *this; }

    template <class T>
    painter& fill_text(const uistring& text, const basic_point<T>& p)
        { return fill_text(text, p.x(), p.y()); }
    ///@}

    ///@{ Draws the given image onto the painter
    painter& draw_image(const image& img, gcoord_type dx, gcoord_type dy)
        { draw_image_raw(img, dx, dy); return *this; }

    template <class T>
    painter& draw_image(const image& img, const basic_point<T>& p)
        { return draw_image(img, p.x(), p.y()); }
    ///@}

    /// Resets the current path
    painter& begin_path()
        { begin_path_raw(); return *this; }

    /// Fills the current path
    painter& fill()
        { fill_raw(); return *this; }

    /// Strokes the current path
    painter& stroke()
        { stroke_raw(); return *this; }

    /// Sets line width (default is 1)
    painter& line_width(gcoord_type width)
        { line_width_raw(width); return *this; }

    /// Sets type of line endings, default value is butt
    painter& line_cap(ui::line_cap lc)
        { line_cap_raw(lc); return *this; }

    /// Sets type of line join, default value is miter
    painter& line_join(ui::line_join lj)
        { line_join_raw(lj); return *this; }

    ///@{ Sets line dashes
    template <class Iterator>
    painter& line_dash(Iterator first, Iterator last)
    {
        std::vector<gcoord_type> segments;
        std::copy(first, last, std::back_inserter(segments));
        line_dash_raw(segments);
        return *this;
    }

    template <class Range>
    painter& line_dash(const Range& r)
        { return line_dash(boost::begin(r), boost::end(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    painter& line_dash(std::initializer_list<T> list)
    {
        std::vector<gcoord_type> segments;
        segments.reserve(list.size());
        std::copy(list.begin(), list.end(), std::back_inserter(segments));
        line_dash_raw(segments);
        return *this;
    }
#endif
    ///@}

    ///@{ Resets line dashes
    painter& line_dash(nullopt_t) { reset_line_dash_raw(); return *this; }
    painter& reset_line_dash() { reset_line_dash_raw(); return *this; }
    ///@}

    /// Sets font
    painter& font(const ui::font& f)
        { font_raw(f); return *this; }

    /// Returns font
    ui::font font() const;

    /// Connects the last point to the first point in the subpath
    painter& close_path()
        { close_path_raw(); return *this; }

    ///@{ Creates a new subpath with the specified point as its first (and only) point
    painter& move_to(gcoord_type x, gcoord_type y)
        { move_to_raw(x, y); return *this; }

    template <class T>
    painter& move_to(const basic_point<T>& p)
        { return move_to(p.x(), p.y()); }
    ///@}

    ///@{ Connects the last point in the subpath to the specified point using a straight line
    painter& line_to(gcoord_type x, gcoord_type y)
        { line_to_raw(x, y); return *this; }

    template <class T>
    painter& line_to(const basic_point<T>& p)
        { return line_to(p.x(), p.y()); }
    ///@}

    ///@{ Creates quadratic Bezier curve with control point (cpx, cpy)
    painter& quadratic_curve_to(gcoord_type cpx, gcoord_type cpy,
                                gcoord_type   x, gcoord_type   y)
        { quadratic_curve_to_raw(cpx, cpy, x, y); return *this; }

    template <class T>
    painter& quadratic_curve_to(const basic_point<T>& cp, const basic_point<T>& p)
        { return quadratic_curve_to(cp.x(), cp.y(), p.x(), p.y()); }
    ///@}

    ///@{ Creates cubic Bezier curve with control points (cp1x, cp1y) and (cp2x, cp2y)
    painter& bezier_curve_to(gcoord_type cp1x, gcoord_type cp1y,
                             gcoord_type cp2x, gcoord_type cp2y,
                             gcoord_type    x, gcoord_type    y)
        { bezier_curve_to_raw(cp1x, cp1y, cp2x, cp2y, x, y); return *this; }

    template <class T>
    painter& bezier_curve_to(const basic_point<T>& cp1,
                             const basic_point<T>& cp2,
                             const basic_point<T>& p)
        { return bezier_curve_to(cp1.x(), cp1.y(), cp2.x(), cp2.y(), p.x(), p.y()); }
    ///@}

    ///@{ Creates an arc
    painter& arc(gcoord_type x, gcoord_type y, gcoord_type radius,
                 gcoord_type start_angle, gcoord_type end_angle, bool anticlockwise = false)
        { arc_raw(x, y, radius, start_angle, end_angle, anticlockwise); return *this; }

    template <class T>
    painter& arc(const basic_point<T>& p, gcoord_type radius,
                 gcoord_type start_angle, gcoord_type end_angle, bool anticlockwise = false)
        { return arc(p.x(), p.y(), radius, start_angle, end_angle, anticlockwise); }
    ///@}

    ///@{ Creates rectangular closed subpath
    painter& rect(gcoord_type x, gcoord_type y, gcoord_type w, gcoord_type h)
        { rect_raw(x, y, w, h); return *this; }

    template <class T>
    painter& rect(const basic_rect<T>& r)
        { return rect(r.x(), r.y(), r.width(), r.height()); }

    template <class T>
    painter& rect(const basic_point<T>& point, const basic_size<T>& size)
        { return rect(point.x(), point.y(), size.width(), size.height()); }

    template <class T>
    painter& rect(const basic_point<T>& point1, const basic_point<T>& point2)
        { return rect(point1.x(), point1.y(), point2.x() - point1.x(), point2.y() - point1.y()); }
    ///@}

    class state_saver;

    /// Implementation-defined painter type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying painter handle
    native_handle_type native_handle();
    ///@}

private:
    void save_raw();
    void restore_raw();
    void scale_raw(gcoord_type x, gcoord_type y);
    void rotate_raw(gcoord_type angle);
    void translate_raw(gcoord_type x, gcoord_type y);
    void fill_color_raw(const color& c);
    void stroke_color_raw(const color& c);
    void clear_rect_raw(gcoord_type x, gcoord_type y, gcoord_type width, gcoord_type height);
    void fill_rect_raw(gcoord_type x, gcoord_type y, gcoord_type width, gcoord_type height);
    void stroke_rect_raw(gcoord_type x, gcoord_type y, gcoord_type width, gcoord_type height);
    void fill_text_raw(const uistring& text, gcoord_type x, gcoord_type y);
    void draw_image_raw(const image& img, gcoord_type dx, gcoord_type dy);
    void begin_path_raw();
    void fill_raw();
    void stroke_raw();
    void line_width_raw(gcoord_type width);
    void line_cap_raw(ui::line_cap lc);
    void line_join_raw(ui::line_join lj);
    void line_dash_raw(const std::vector<gcoord_type>& segments);
    void reset_line_dash_raw();
    void font_raw(const ui::font& f);
    void close_path_raw();
    void move_to_raw(gcoord_type x, gcoord_type y);
    void line_to_raw(gcoord_type x, gcoord_type y);
    void quadratic_curve_to_raw(gcoord_type cpx, gcoord_type cpy,
                                gcoord_type   x, gcoord_type   y);
    void bezier_curve_to_raw(gcoord_type cp1x, gcoord_type cp1y,
                             gcoord_type cp2x, gcoord_type cp2y,
                             gcoord_type    x, gcoord_type    y);
    void arc_raw(gcoord_type x, gcoord_type y, gcoord_type radius,
                 gcoord_type start_angle, gcoord_type end_angle, bool anticlockwise);
    void rect_raw(gcoord_type x, gcoord_type y, gcoord_type w, gcoord_type h);

    detail::painter_impl* m_impl;

    friend class canvas;
};

/// @brief Saves state in the constructor and restores it in the destructor
/// @ingroup graphics

class painter::state_saver : private boost::noncopyable
{
public:
    /// Saves current painter state in the stack
    state_saver(painter& c) : m_painter(c) { m_painter.save(); }

    /// Restores painter state from the stack
    ~state_saver() { m_painter.restore(); }

private:
    painter& m_painter;
};

/// @brief 2D size geometry coordinates
/// @ingroup coord
typedef basic_size<painter::gcoord_type> gsize;

/// @brief 2D point geometry coordinates
/// @ingroup coord
typedef basic_point<painter::gcoord_type> gpoint;

/// @brief 2D rectangle geometry coordinates
/// @ingroup coord
typedef basic_rect<painter::gcoord_type> grect;

} // namespace ui
} // namespace boost

#endif // BOOST_UI_PAINTER_HPP
