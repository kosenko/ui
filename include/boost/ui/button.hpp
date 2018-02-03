// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file button.hpp Button widget

#ifndef BOOST_UI_BUTTON_HPP
#define BOOST_UI_BUTTON_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>
#include <boost/ui/detail/event.hpp>

namespace boost {
namespace ui    {

/// @brief Widget with label that generate event when clicked on
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp button
/// @see <a href="http://en.wikipedia.org/wiki/Button_(computing)">Button (Wikipedia)</a>
/// @ingroup command

class BOOST_UI_DECL button : public widget
{
public:
    button() {}

    ///@{ @brief Creates button with text label with mnemonics
    /// @see <a href="https://en.wikipedia.org/wiki/Mnemonics_(keyboard)">Mnemonics (Wikipedia)</a>
    explicit button(widget& parent, const uistring& label)
        { create(parent, label); }
    button& create(widget& parent, const uistring& label);
    ///@}

    /// Connects button press handler
    BOOST_UI_DETAIL_HANDLER(press, button);

private:
    void on_press_raw(const boost::function<void()>& handler);

    class detail_impl;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_BUTTON_HPP
