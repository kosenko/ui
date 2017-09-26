// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file webview.hpp WebView widget

#ifndef BOOST_UI_WEBVIEW_HPP
#define BOOST_UI_WEBVIEW_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that renders HTML
/// @see <a href="http://en.wikipedia.org/wiki/Web_browser_engine">Web browser engine (Wikipedia)</a>
/// @see <a href="http://www.w3.org/TR/html-markup/iframe.html">iframe (W3C)</a>
/// @ingroup info

class BOOST_UI_DECL webview : public widget
{
public:
    webview() {}

    ///@{ Creates webview widget
    explicit webview(widget& parent)
        { create(parent); }
    webview& create(widget& parent);
    ///@}

    /// @brief Sets HTML content
    /// @see <a href="http://en.wikipedia.org/wiki/HTML">HTML (Wikipedia)</a>
    webview& html(const uistring& html);

    /// @brief Loads content from the URL
    /// @see <a href="http://en.wikipedia.org/wiki/Uniform_resource_locator">Uniform resource locator (Wikipedia)</a>
    webview& load(const uistring& url);

private:
    class detail_impl;
    detail_impl* get_impl();
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_WEBVIEW_HPP
