// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file progressbar.hpp Progress bar widget

#ifndef BOOST_UI_PROGRESSBAR_HPP
#define BOOST_UI_PROGRESSBAR_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Progress bar widget base class
/// @see <a href="http://en.wikipedia.org/wiki/Progress_bar">Progress bar (Wikipedia)</a>
/// @ingroup info

class BOOST_UI_DECL progressbar : public widget
{
public:
    /// Progress bar value type
    typedef int value_type;

    /// @brief Sets value position
    /// @throw std::out_of_range If @a value is out of range
    progressbar& value(value_type value);

    /// Returns value position
    value_type value() const;

    /// Returns maximum value position
    value_type max() const;

protected:
    progressbar() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, bool horizontal, value_type initial,
                       value_type max);
#endif

private:
    void check_range(value_type value) const
        { check_range(value, max()); }
    static void check_range(value_type value, value_type max);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

/// @brief Horizontal progress bar widget
/// @ingroup info

class BOOST_UI_DECL hprogressbar : public progressbar
{
public:
    hprogressbar() {}

    ///@{ @brief Creates horizontal progress bar
    /// @throw std::out_of_range
    explicit hprogressbar(widget& parent, value_type initial = 0,
                          value_type max = 100)
        { create(parent, initial, max); }
    hprogressbar& create(widget& parent, value_type initial = 0,
                         value_type max = 100)
        { detail_create(parent, true, initial, max); return *this; }
    ///@}
};

/// @brief Vertical progress bar widget
/// @ingroup info

class BOOST_UI_DECL vprogressbar : public progressbar
{
public:
    vprogressbar() {}

    ///@{ @brief Creates vertical progress bar
    /// @throw std::out_of_range
    explicit vprogressbar(widget& parent, value_type initial = 0,
                          value_type max = 100)
        { create(parent, initial, max); }
    vprogressbar& create(widget& parent, value_type initial = 0,
                         value_type max = 100)
        { detail_create(parent, false, initial, max); return *this; }
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_PROGRESSBAR_HPP
