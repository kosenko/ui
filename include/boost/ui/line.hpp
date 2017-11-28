// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file line.hpp line widget

#ifndef BOOST_UI_LINE_HPP
#define BOOST_UI_LINE_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Abstract widget that displays horizontal or vertical line
/// @ingroup info

class BOOST_UI_DECL line_widget : public widget
{
protected:
    line_widget() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, bool horizontal);
#endif

private:
    class detail_impl;
};

/// @brief Horizontal line widget
/// @ingroup info

class BOOST_UI_DECL hline : public line_widget
{
public:
    hline() {}

    ///@{ Creates horizontal line widget
    explicit hline(widget& parent)
        { create(parent); }
    hline& create(widget& parent)
        { detail_create(parent, true); return *this; }
    ///@}

};

/// @brief Vertical line widget
/// @ingroup info

class BOOST_UI_DECL vline : public line_widget
{
public:
    vline() {}

    ///@{ Creates vertical line widget
    explicit vline(widget& parent)
        { create(parent); }
    vline& create(widget& parent)
        { detail_create(parent, false); return *this; }
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LINE_HPP
