// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file web_widget.hpp Web widget

#ifndef BOOST_UI_WEB_WIDGET_HPP
#define BOOST_UI_WEB_WIDGET_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that renders HTML
/// @see <a href="http://en.wikipedia.org/wiki/Web_browser_engine">Web browser engine (Wikipedia)</a>
/// @see <a href="http://www.w3.org/TR/html-markup/iframe.html">iframe (W3C)</a>
/// @ingroup info

class BOOST_UI_DECL web_widget : public widget
{
public:
    web_widget() {}

    ///@{ Creates web_widget widget
    explicit web_widget(widget& parent)
        { create(parent); }
    web_widget& create(widget& parent);
    ///@}

    /// @brief Sets HTML content
    /// @see <a href="http://en.wikipedia.org/wiki/HTML">HTML (Wikipedia)</a>
    web_widget& html(const uistring& html);

    /// @brief Loads content from the URL
    /// @see <a href="http://en.wikipedia.org/wiki/Uniform_resource_locator">Uniform resource locator (Wikipedia)</a>
    web_widget& load(const uistring& url);

private:
    class detail_impl;
    detail_impl* get_impl();
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_WEB_WIDGET_HPP
