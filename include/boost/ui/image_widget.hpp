// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file image_widget.hpp Image widget

#ifndef BOOST_UI_IMAGE_WIDGET_HPP
#define BOOST_UI_IMAGE_WIDGET_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>
#include <boost/ui/image.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that displays image
/// @see boost::ui::image
/// @ingroup info

class BOOST_UI_DECL image_widget : public widget
{
public:
    image_widget() { init(); }

    ///@{ Creates image_widget without image
    explicit image_widget(widget& parent)
        { init(); create(parent); }
    image_widget& create(widget& parent);
    ///@}

    ///@{ Creates image_widget with image
    explicit image_widget(widget& parent, const ui::image& img)
        { init(); create(parent, img); }
    image_widget& create(widget& parent, const ui::image& img);
    ///@}

    /// Sets image
    image_widget& image(const image& img);

    /// Clears image
    void clear();

private:
    void init() {}

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_IMAGE_WIDGET_HPP
