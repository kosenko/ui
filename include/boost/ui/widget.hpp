// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file widget.hpp Widget class

#ifndef BOOST_UI_WIDGET_HPP
#define BOOST_UI_WIDGET_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/coord.hpp>
#include <boost/ui/string.hpp>
#include <boost/ui/event.hpp>
#include <boost/ui/font.hpp>
#include <boost/ui/layout.hpp>
#include <boost/ui/detail/shared_count.hpp>

/// Boost C++ libraries namespace
namespace boost {
/// Boost.UI library namespace
namespace ui    {


#ifndef DOXYGEN

namespace detail {
class widget_detail_base;
} // namespace detail

#endif

/// @brief Base class for all widgets
/// @see <a href="http://en.wikipedia.org/wiki/Widget_(GUI)">Widget (Wikipedia)</a>
/// @see <a href="http://en.wikipedia.org/wiki/Graphical_user_interface_elements">
///     Graphical user interface elements (Wikipedia)</a>
/// @ingroup widget

class BOOST_UI_DECL widget
{
public:
    widget();
    virtual ~widget();

#ifndef DOXYGEN
    widget(const widget& other);
    widget& operator=(const widget& other);
#endif

    /// Returns @ref layout::item with this widget
    ui::layout::item layout()
        { return ui::layout::item(*this); }

    ///@{ Creates native widget and appends it to this widget
    widget& append(const widget& w);
    widget& operator<<(const widget& w)
        { return append(w); }
    ///@}

    ///@{ Moves widget to specified position
    widget& move(coord_type x, coord_type y);
    widget& move(const point& pos)
        { move(pos.x(), pos.y()); return *this; }
    ///@}

    /// Changes widget size to specified values
    widget& resize(coord_type width, coord_type height);

    /// Returns x coordinate relative to the parent widget client area
    coord_type x() const;

    /// Returns y coordinate relative to the parent widget client area
    coord_type y() const;

    /// Returns widget width
    coord_type width() const;

    /// Returns widget height
    coord_type height() const;

    /// Returns widget position relative to the parent widget client area
    point pos() const { return point(x(), y()); }

    /// Returns widget size
    size dimensions() const
        { return size(width(), height()); }

    /// Returns widget bounds in client coordinates
    rect bounds() const
        { return rect(x(), y(), width(), height()); }

    /// Enables widget if @a do_enable is true, disables otherwise
    widget& enable(bool do_enable = true);

    /// Disables widget
    widget& disable() { return enable(false); }

    /// Returns true if widget is enabled, false otherwise
    bool is_enabled() const;

    /// Shows widget if @a do_show is true, hides otherwise
    widget& show(bool do_show = true);

    /// Hides widget
    widget& hide() { return show(false); }

    /// Returns true if widget is shown on screen, false otherwise
    bool is_shown() const;

    /// @brief Sets tooltip text
    /// @see <a href="http://en.wikipedia.org/wiki/Tooltip">Tooltip (Wikipedia)</a>
    widget& tooltip(const uistring& text);

    /// Returns tooltip text
    uistring tooltip() const;

    /// Sets font
    widget& font(const ui::font& f);

    /// Returns font
    ui::font font() const;

    ///@{ Connects widget resize handler
    widget& on_resize(const boost::function<void()>& hanlder);
    ///@}

    ///@{ Connects keyboard event handler
    widget& on_key_press(const boost::function<void()>& handler);
    widget& on_key_press_event(const boost::function<void(key_event&)>& handler);
    widget& on_key_down(const boost::function<void()>& handler);
    widget& on_key_down_event(const boost::function<void(key_event&)>& handler);
    widget& on_key_up(const boost::function<void()>& handler);
    widget& on_key_up_event(const boost::function<void(key_event&)>& handler);
    ///@}

    ///@{ Connects mouse event handler
    widget& on_left_mouse_down(const boost::function<void()>& handler);
    widget& on_left_mouse_down_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_left_mouse_up(const boost::function<void()>& handler);
    widget& on_left_mouse_up_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_right_mouse_down(const boost::function<void()>& handler);
    widget& on_right_mouse_down_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_right_mouse_up(const boost::function<void()>& handler);
    widget& on_right_mouse_up_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_middle_mouse_down(const boost::function<void()>& handler);
    widget& on_middle_mouse_down_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_middle_mouse_up(const boost::function<void()>& handler);
    widget& on_middle_mouse_up_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_left_mouse_double_click(const boost::function<void()>& handler);
    widget& on_left_mouse_double_click_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_right_mouse_double_click(const boost::function<void()>& handler);
    widget& on_right_mouse_double_click_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_middle_mouse_double_click(const boost::function<void()>& handler);
    widget& on_middle_mouse_double_click_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_mouse_move(const boost::function<void()>& handler);
    widget& on_mouse_move_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_mouse_drag(const boost::function<void()>& handler);
    widget& on_mouse_drag_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_mouse_enter(const boost::function<void()>& handler);
    widget& on_mouse_enter_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_mouse_leave(const boost::function<void()>& handler);
    widget& on_mouse_leave_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_context_menu(const boost::function<void()>& handler);
    widget& on_context_menu_event(const boost::function<void(mouse_event&)>& handler);
    widget& on_mouse_wheel(const boost::function<void()>& handler);
    widget& on_mouse_wheel_event(const boost::function<void(wheel_event&)>& handler);
    ///@}

    /// Returns true only if native widget was created
    bool native_valid() const BOOST_NOEXCEPT { return native_handle() != NULL; }

    /// Implementation-defined widget type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying widget handle
    native_handle_type native_handle();
    const native_handle_type native_handle() const;
    ///@}

protected:
#ifndef DOXYGEN
    void detail_set_detail_impl(detail::widget_detail_base* d);
    template <class TDetail>
    TDetail* get_detail_impl() { return dynamic_cast<TDetail*>(m_detail_impl); }
    template <class TDetail>
    const TDetail* get_detail_impl() const { return dynamic_cast<const TDetail*>(m_detail_impl); }
#endif

private:
    void delete_last_detail_impl();

    detail::widget_detail_base* m_detail_impl;
    detail::shared_count m_shared_count;
};

/// @brief Widget that wraps previously created native widget
/// @ingroup widget

class BOOST_UI_DECL native_widget : public widget
{
public:
    /// Creates widget from native widget handle
    explicit native_widget(native_handle_type handle);
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_WIDGET_HPP
