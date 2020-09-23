// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file layout.hpp @brief Layout classes

#ifndef BOOST_UI_LAYOUT_HPP
#define BOOST_UI_LAYOUT_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace ui    {

class widget;
class box_layout;

/// @brief Base class for all layouts
/// @ingroup layout

class BOOST_UI_DECL layout
{
public:
    class item;
};

/// @brief Layout item with arrangement parameters
/// @ingroup layout

class BOOST_UI_DECL layout::item
{
    class impl;

public:
    item();
    /// Constructs widget item
    item(const widget& w);
    /// Constructs layout item
    item(const box_layout& l);
    ~item();

#ifndef DOXYGEN
    item(const item& other);
    item& operator=(const item& other);
#endif

    ///@{ @brief Appends subitem
    item& append(const item& item);
    item& operator<<(const item& item)
        { return append(item); }
    ///@}

    /// Resets layout item margin
    item& no_margin()
        { return margin(0); }

    ///@{ Sets layout item margin in spaces, that are backed-dependent
    item& margin(int all)
        { return margin(all, all); }
    item& margin(int vertical, int horizontal)
        { return margin(vertical, horizontal, vertical, horizontal); }
    item& margin(int top, int right, int bottom, int left);
    ///@}

    ///@{ Sets layout item margin in pixels
    item& margin_px(int all)
        { return margin_px(all, all); }
    item& margin_px(int vertical, int horizontal)
        { return margin_px(vertical, horizontal, vertical, horizontal); }
    item& margin_px(int top, int right, int bottom, int left);
    ///@}

    /// Sets layout item stretch factor
    item& stretch(int value = 1);

    ///@{ Sets layout item align
    item& left();
    item& right();
    item& top();
    item& bottom();
    item& vcenter();
    item& hcenter();
    item& center();
    item& justify();
    ///@}

private:
    impl* m_impl;
    widget* m_widget;
    box_layout* m_layout;
#ifndef DOXYGEN
    friend class box_layout;
#endif
};

/// @brief Abstract vertical or horizontal box layout
/// @ingroup layout

class BOOST_UI_DECL box_layout : public layout
{
public:
    /// Returns @ref layout::item with this widget
    item layout()
        { return ui::layout::item(*this); }

    ///@{ Appends a layout item to the layout
    box_layout& append(const item& item);
    box_layout& operator<<(const item& item)
        { return append(item); }
    ///@}

protected:
#ifndef DOXYGEN
    explicit box_layout(bool horizontal);
    explicit box_layout(widget& parent, bool horizontal);
#endif

private:
    class impl;
    impl* m_impl;
};

/// @brief Horizontal box layout
/// @ingroup layout

class BOOST_UI_DECL hbox : public box_layout
{
public:
    hbox() : box_layout(true) {}

    /// Constructs and sets layout to the widget
    explicit hbox(widget& parent) : box_layout(parent, true) {}
};

/// @brief Vertical box layout
/// @ingroup layout

class BOOST_UI_DECL vbox : public box_layout
{
public:
    vbox() : box_layout(false) {}

    /// Constructs and sets layout to the widget
    explicit vbox(widget& parent) : box_layout(parent, false) {}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LAYOUT_HPP
