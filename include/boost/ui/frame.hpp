// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file frame.hpp Frame widget

#ifndef BOOST_UI_FRAME_HPP
#define BOOST_UI_FRAME_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/window.hpp>
#include <boost/ui/menu.hpp>
#include <boost/ui/status_bar.hpp>

namespace boost {
namespace ui    {

/// @brief Top level widget that hosts other widgets and supports menu bar
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp frame
/// @see <a href="http://en.wikipedia.org/wiki/Window_(computing)">Window (Wikipedia)</a>
/// @ingroup tlw

class BOOST_UI_DECL frame : public window
{
public:
    frame() {}

    ///@{ Creates frame with the title
    explicit frame(const uistring& title)
        { create(title); }
    frame& create(const uistring& title);
    ///@}

    /// @brief Returns menu bar
    /// @details If menu bar wasn't created, creates menu bar.
    ui::menu_bar menu_bar();

    /// @brief Returns status bar
    /// @details If status bar wasn't created, creates status bar.
    ui::status_bar status_bar();

private:
    class detail_impl;
    detail_impl* get_impl();
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_FRAME_HPP
