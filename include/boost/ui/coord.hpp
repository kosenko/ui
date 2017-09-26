// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file coord.hpp Coordinates classes

#ifndef BOOST_UI_COORD_HPP
#define BOOST_UI_COORD_HPP

#ifdef DOXYGEN
/// @brief Enables Boost.Geometry
/// @ingroup coord
#define BOOST_UI_USE_GEOMETRY

/// @brief Enables Boost.Polygon
/// @ingroup coord
#define BOOST_UI_USE_POLYGON
#endif

#if defined(BOOST_UI_USE_GEOMETRY) && defined(BOOST_UI_USE_POLYGON)
#error Unable to use Boost.Geometry with Boost.Polygon
#endif

#include <boost/ui/config.hpp>

#ifdef BOOST_UI_USE_GEOMETRY
#include <boost/geometry.hpp> // TODO: Remove hotfix
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/box.hpp>
#endif

#ifdef BOOST_UI_USE_POLYGON
#include <boost/polygon/point_data.hpp>
#include <boost/polygon/rectangle_data.hpp>
#endif

namespace boost {
namespace ui    {

/// @brief 2D size of object data structure with custom coordinates type
/// @ingroup coord
template <class T>
class basic_size
{
public:
    /// Constructs empty size object
    basic_size() : m_width(T()), m_height(T()) {}

    /// Constructs size with width and height
    basic_size(const T& width, const T& height)
        : m_width(width), m_height(height) {}

    /// Constructs size with an other size object
    template <class D>
    explicit basic_size(const basic_size<D>& s)
        : m_width(s.width()), m_height(s.height()) {}

    ///@{ Compares two sizes
    bool operator==(const basic_size& other) const
        { return m_width == other.m_width && m_height == other.m_height; }
    bool operator!=(const basic_size& other) const
        { return !operator==(other); }
    ///@}

    /// Retruns width
    const T& width() const { return m_width; }

    /// Retruns height
    const T& height() const { return m_height; }

    ///@{ Arithmetic operation
    basic_size& operator*=(const T& value)
    {
        m_width  *= value;
        m_height *= value;
        return *this;
    }
    basic_size& operator/=(const T& value)
    {
        m_width  /= value;
        m_height /= value;
        return *this;
    }
    ///@}

private:
    T m_width;
    T m_height;
};

///@{ Arithmetic operation
template <class T>
basic_size<T> operator*(const T& value, const basic_size<T>& rhs)
{
    return basic_size<T>(value * rhs.width(), value * rhs.height());
}
template <class T>
basic_size<T> operator*(const basic_size<T>& lhs, const T& value)
{
    return basic_size<T>(lhs.width() * value, lhs.height() * value);
}
template <class T>
basic_size<T> operator/(const basic_size<T>& lhs, const T& value)
{
    return basic_size<T>(lhs.width() / value, lhs.height() / value);
}
///@}

/// @brief 2D point data structure with custom coordinates type
/// @see <a href="http://en.wikipedia.org/wiki/Point_(geometry)">Point (Wikipedia)</a>
/// @ingroup coord

template <class T>
class basic_point
#ifdef BOOST_UI_USE_GEOMETRY
    : public ::boost::geometry::model::d2::point_xy<T>
#endif
#ifdef BOOST_UI_USE_POLYGON
    : public ::boost::polygon::point_data<T>
#endif
{
#if defined(BOOST_UI_USE_GEOMETRY)
    typedef ::boost::geometry::model::d2::point_xy<T> base_type;
#elif defined(BOOST_UI_USE_POLYGON)
    typedef ::boost::polygon::point_data<T> base_type;
#endif

public:

    /// Type of coordinates
    typedef T value_type;

    /// Constructs point with empty coordinates
    basic_point() :
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        base_type(T(), T())
#else
        m_x(T()), m_y(T())
#endif
    {}

    /// Constructs point with x and y coordinates
    basic_point(const T& x, const T& y) :
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        base_type(x, y)
#else
        m_x(x), m_y(y)
#endif
    {}

#if (defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)) && !defined(DOXYGEN)
    basic_point(const base_type& p) : base_type(p) {}
#endif

    /// Constructs size with an other size object
    template <class D>
    explicit basic_point(const basic_point<D>& p) :
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        base_type(p.x(), p.y())
#else
        m_x(p.x()), m_y(p.y())
#endif
    {}

    /// Returns x coordinate
    T x() const
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        { return base_type::x(); }
#else
        { return m_x; }
#endif

    /// Returns y coordinate
    T y() const
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        { return base_type::y(); }
#else
        { return m_y; }
#endif

    /// Sets x coordinate
    void x(const T& x)
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        { base_type::x(x); }
#else
        { m_x = x; }
#endif

    /// Sets y coordinate
    void y(const T& y)
#if defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)
        { base_type::y(y); }
#else
        { m_y = y; }
#endif

    ///@{ Compares two points
    bool operator==(const basic_point& other) const
        { return x() == other.x() && y() == other.y(); }
    bool operator!=(const basic_point& other) const
        { return !operator==(other); }
    ///@}

    ///@{ Arithmetic operation
    basic_point& operator+=(const basic_size<T>& other)
    {
        x(x() + other.width());
        y(y() + other.height());
        return *this;
    }
    basic_point& operator-=(const basic_size<T>& other)
    {
        x(x() - other.width());
        y(y() - other.height());
        return *this;
    }
    ///@}

private:
#if !defined(BOOST_UI_USE_GEOMETRY) && !defined(BOOST_UI_USE_POLYGON)
    T m_x;
    T m_y;
#endif
};

///@{ Arithmetic operation
template <class T>
basic_point<T> operator+(const basic_point<T>& lhs,
                         const basic_size<T>& rhs)
{
    return basic_point<T>(lhs.x() + rhs.width(), lhs.y() + rhs.height());
}

template <class T>
basic_point<T> operator-(const basic_point<T>& lhs,
                         const basic_size<T>& rhs)
{
    return basic_point<T>(lhs.x() - rhs.width(), lhs.y() - rhs.height());
}

template <class T>
basic_size<T> operator-(const basic_point<T>& lhs,
                        const basic_point<T>& rhs)
{
    return basic_size<T>(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}
///@}

/// @brief 2D rectangle plane figure data structure with custom coordinates type
/// @see <a href="http://en.wikipedia.org/wiki/Rectangle">Rectangle (Wikipedia)</a>
/// @ingroup coord

template <class T>
class basic_rect
#ifdef BOOST_UI_USE_GEOMETRY
    : public ::boost::geometry::model::box<
        ::boost::geometry::model::d2::point_xy<T> >
#endif
#ifdef BOOST_UI_USE_POLYGON
    : public ::boost::polygon::rectangle_data<T>
#endif
{
#ifdef BOOST_UI_USE_GEOMETRY
    typedef ::boost::geometry::model::d2::point_xy<T> point_type;
    typedef ::boost::geometry::model::box<point_type> base_type;
#endif
#ifdef BOOST_UI_USE_POLYGON
    typedef ::boost::polygon::rectangle_data<T> base_type;
#endif

public:
    /// Type of coordinates
    typedef T value_type;

    /// Constructs rectangle with empty coordinates
    basic_rect()
#if defined(BOOST_UI_USE_GEOMETRY)
        : base_type(point_type(T(), T()), point_type(T(), T()))
#elif defined(BOOST_UI_USE_POLYGON)
        : base_type(T(), T(), T(), T())
#endif
    {}

    ///@{ Constructs rectangle with coordinates
    basic_rect(const T& x, const T& y, const T& width, const T& height) :
#if defined(BOOST_UI_USE_GEOMETRY)
        base_type(point_type(x,         y),
                  point_type(x + width, y + height))
#elif defined(BOOST_UI_USE_POLYGON)
        base_type(x,         y,
                  x + width, y + height)
#else
        m_point(x, y), m_size(width, height)
#endif
    {}

    basic_rect(const basic_point<T>& point, const basic_size<T>& size) :
#if defined(BOOST_UI_USE_GEOMETRY)
        base_type(point_type(point.x(),                point.y()),
                  point_type(point.x() + size.width(), point.y() + size.height()))
#elif defined(BOOST_UI_USE_POLYGON)
        base_type(point.x(),                point.y(),
                  point.x() + size.width(), point.y() + size.height())
#else
        m_point(point.x(), point.y()), m_size(size.width(), size.height())
#endif
    {}

    basic_rect(const basic_point<T>& point1, const basic_point<T>& point2) :
#if defined(BOOST_UI_USE_GEOMETRY)
        base_type(point_type(point1.x(), point1.y()),
                  point_type(point2.x(), point2.y()))
#elif defined(BOOST_UI_USE_POLYGON)
        base_type(point1.x(), point1.y(),
                  point2.x(), point2.y())
#else
        m_point(point1.x(), point1.y()), m_size(point2 - point1)
#endif
    {}

#if (defined(BOOST_UI_USE_GEOMETRY) || defined(BOOST_UI_USE_POLYGON)) && !defined(DOXYGEN)
    basic_rect(const base_type& other) : base_type(other) {}
#endif

    template <class D>
    explicit basic_rect(const basic_rect<D>& other) :
#if defined(BOOST_UI_USE_GEOMETRY)
        base_type(point_type(other.x(), other.y()),
                  point_type(static_cast<T>(other.x()) +
                                 static_cast<T>(other.width()),
                             static_cast<T>(other.y()) +
                                 static_cast<T>(other.height())))
#elif defined(BOOST_UI_USE_POLYGON)
        base_type(other.x(), other.y(),
                  static_cast<T>(other.x()) +
                      static_cast<T>(other.width()),
                  static_cast<T>(other.y()) +
                      static_cast<T>(other.height()))
#else
        m_point(other.x(), other.y()), m_size(other.width(), other.height())
#endif
    {}

    ///@}

    /// Returns x coordinate
    T x() const
#if defined(BOOST_UI_USE_GEOMETRY)
        { return this->min_corner().x(); }
#elif defined(BOOST_UI_USE_POLYGON)
        { return this->get(::boost::polygon::HORIZONTAL).low(); }
#else
        { return m_point.x(); }
#endif

    /// Returns y coordinate
    T y() const
#if defined(BOOST_UI_USE_GEOMETRY)
        { return this->min_corner().y(); }
#elif defined(BOOST_UI_USE_POLYGON)
        { return this->get(::boost::polygon::VERTICAL).low(); }
#else
        { return m_point.y(); }
#endif

    /// Returns width
    T width() const
#if defined(BOOST_UI_USE_GEOMETRY)
        { return this->max_corner().x() - this->min_corner().x(); }
#elif defined(BOOST_UI_USE_POLYGON)
        { return this->get(::boost::polygon::HORIZONTAL).high() -
                 this->get(::boost::polygon::HORIZONTAL).low(); }
#else
        { return m_size.width(); }
#endif

    /// Returns height
    T height() const
#if defined(BOOST_UI_USE_GEOMETRY)
        { return this->max_corner().y() - this->min_corner().y(); }
#elif defined(BOOST_UI_USE_POLYGON)
        { return this->get(::boost::polygon::VERTICAL).high() -
                 this->get(::boost::polygon::VERTICAL).low(); }
#else
        { return m_size.height(); }
#endif

    ///@{ Compares two rectangles
    bool operator==(const basic_rect& other) const
    {
        return x()     == other.x()     && y()      == other.y() &&
               width() == other.width() && height() == other.height();
    }
    bool operator!=(const basic_rect& other) const
        { return !operator==(other); }
    ///@}

private:
#if !defined(BOOST_UI_USE_GEOMETRY) && !defined(BOOST_UI_USE_POLYGON)
    basic_point<T> m_point;
    basic_size<T> m_size;
#endif
};

/// @brief Widget coordinates signed number type
/// @ingroup coord
typedef int coord_type;

/// @brief 2D size coordinates
/// @ingroup coord
typedef basic_size<coord_type> size;

/// @brief 2D point coordinates
/// @ingroup coord
typedef basic_point<coord_type> point;

/// @brief 2D rectangle coordinates
/// @ingroup coord
typedef basic_rect<coord_type> rect;

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COORD_HPP
