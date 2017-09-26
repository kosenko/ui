// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file button.hpp Button widget

#ifndef BOOST_UI_BUTTON_HPP
#define BOOST_UI_BUTTON_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#include <boost/move/utility.hpp>
#else
#include <boost/bind.hpp>
#endif

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

    ///@{ Creates button with label string
    explicit button(widget& parent, const uistring& label)
        { create(parent, label); }
    button& create(widget& parent, const uistring& label);
    ///@}

    /// Connects button press handler
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    template <class F, class ...Args>
    button& on_press(F&& f, Args&&... args)
        { on_press_raw(std::bind(boost::forward<F>(f), boost::forward<Args>(args)...)); return *this; }
#else
    button& on_press(const boost::function<void()>& handler)
        { on_press_raw(handler); return *this; }

    template <class F, class Arg1>
    button& on_press(F f, Arg1 a1)
        { on_press_raw(boost::bind(f, a1)); return *this; }
#endif

private:
    void on_press_raw(const boost::function<void()>& handler);

    class detail_impl;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_BUTTON_HPP
