// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file canvas.hpp Canvas widget

#ifndef BOOST_UI_CANVAS_HPP
#define BOOST_UI_CANVAS_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>
#include <boost/ui/painter.hpp>

namespace boost {
namespace ui    {

/// @brief Widget for drawing
/// @see boost::ui::painter
/// @see <a href="http://en.wikipedia.org/wiki/Canvas_(GUI)">Canvas (Wikipedia)</a>
/// @ingroup info
/// @ingroup graphics

class BOOST_UI_DECL canvas : public widget
{
public:
    canvas() {}

    ///@{ Creates canvas widget.
    explicit canvas(widget& parent)
        { create(parent); }
    canvas& create(widget& parent);
    ///@}

    /// @brief Returns painter based on this canvas
    /// to work in the <a href="http://en.wikipedia.org/wiki/Retained_mode">retained mode</a>
    ui::painter painter();

private:
    detail::painter_impl* get_impl();

#ifndef DOXYGEN
    friend class painter;
#endif
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_CANVAS_HPP
