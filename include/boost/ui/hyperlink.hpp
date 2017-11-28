// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file hyperlink.hpp Hyperlink widget

#ifndef BOOST_UI_HYPERLINK_HPP
#define BOOST_UI_HYPERLINK_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that displays static text which links to an URL
/// @see <a href="http://en.wikipedia.org/wiki/Hyperlink">Hyperlink (Wikipedia)</a>
/// @ingroup command

class BOOST_UI_DECL hyperlink : public widget
{
public:
    hyperlink() {}

    ///@{ Creates hyperlink widget with URL and text
    explicit hyperlink(widget& parent, const uistring& url, const uistring& text)
        { create(parent, url, text); }
    hyperlink& create(widget& parent, const uistring& url, const uistring& text);
    ///@}

private:
    class detail_impl;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_HYPERLINK_HPP
