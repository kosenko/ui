// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file slider.hpp Slider widget

#ifndef BOOST_UI_SLIDER_HPP
#define BOOST_UI_SLIDER_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Slider widget base class
/// @see <a href="http://en.wikipedia.org/wiki/Slider_(computing)">Slider (Wikipedia)</a>
/// @ingroup io

class BOOST_UI_DECL slider : public widget
{
public:
    /// Slider value type
    typedef int value_type;

    /// Retruns position value
    value_type value() const;

    /// Retruns minimum position value
    value_type min() const;

    /// Retruns maximum position value
    value_type max() const;

    /// Connects slide handler
    slider& on_slide(const boost::function<void()>& handler);

    /// Connects slide end handler
    slider& on_slide_end(const boost::function<void()>& handler);

protected:
    slider() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, bool horizontal, value_type initial,
                       value_type min, value_type max);
#endif

private:
    void check_range(value_type value) const
        { check_range(value, min(), max()); }
    static void check_range(value_type value, value_type min, value_type max);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

/// @brief Horizontal slider widget
/// @ingroup io

class BOOST_UI_DECL hslider : public slider
{
public:
    hslider() {}

    ///@{ @brief Creates horizontal slider
    /// @throw std::out_of_range
    explicit hslider(widget& parent, value_type initial,
                     value_type min, value_type max)
        { create(parent, initial, min, max); }
    explicit hslider(widget& parent, value_type initial = 0)
        { create(parent, initial); }
    hslider& create(widget& parent, value_type initial,
                    value_type min, value_type max)
        { detail_create(parent, true, initial, min, max); return *this; }
    hslider& create(widget& parent, value_type initial = 0)
        { return create(parent, initial, 0, 100); }
    ///@}
};

/// @brief Vertical slider widget
/// @ingroup io

class BOOST_UI_DECL vslider : public slider
{
public:
    vslider() {}

    ///@{ @brief Creates vertical slider
    /// @throw std::out_of_range
    explicit vslider(widget& parent, value_type initial,
                     value_type min, value_type max)
        { create(parent, initial, min, max); }
    explicit vslider(widget& parent, value_type initial = 0)
        { create(parent, initial); }
    vslider& create(widget& parent, value_type initial,
                    value_type min, value_type max)
        { detail_create(parent, false, initial, min, max); return *this; }
    vslider& create(widget& parent, value_type initial = 0)
        { return create(parent, initial, 0, 100); }
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_SLIDER_HPP
