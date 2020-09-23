// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file panel.hpp @brief Panel widget

#ifndef BOOST_UI_PANEL_HPP
#define BOOST_UI_PANEL_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that hosts other widgets
/// @see <a href="http://en.wikipedia.org/wiki/Panel_(computer_software)">Panel (Wikipedia)</a>
/// @ingroup container

class BOOST_UI_DECL panel : public widget
{
public:
    panel() {}

    ///@{ Creates panel widget
    explicit panel(panel& other) { create(other); }
    explicit panel(widget& parent) { create(parent); }
    panel& create(widget& parent);
    ///@}

private:
    class detail_impl;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_PANEL_HPP
