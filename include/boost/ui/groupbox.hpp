// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file groupbox.hpp Group box widget

#ifndef BOOST_UI_GROUPBOX_HPP
#define BOOST_UI_GROUPBOX_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that groups other widgets using a frame and a title
/// @see <a href="http://en.wikipedia.org/wiki/Frame_(GUI)">Frame (Wikipedia)</a>
/// @ingroup container

class BOOST_UI_DECL groupbox : public widget
{
public:
    groupbox() {}

    ///@{ Creates groupbox widget
    explicit groupbox(widget& parent, const uistring& title = uistring())
        { create(parent, title); }
    groupbox& create(widget& parent, const uistring& title = uistring());
    ///@}

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_GROUPBOX_HPP
