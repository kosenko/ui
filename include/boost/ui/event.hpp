// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file event.hpp Event classes

#ifndef BOOST_UI_EVENT_HPP
#define BOOST_UI_EVENT_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/coord.hpp>

#include <boost/function.hpp>

namespace boost  {
namespace ui     {

#ifndef DOXYGEN
namespace native {

template <class NativeEvent, class UIEvent>
class event_functor_event;

} // namespace native
#endif

/// @brief Base class for all events
/// @ingroup event

class event
{
public:
    virtual ~event() {}
};

/// @brief Integral type for indexing items
/// @ingroup widget
typedef int index_type;
//typedef std::size_t index_type;

/// @brief Invalid index value
/// @ingroup widget
const index_type nindex = -1;

/// @brief Event class that holds some index in container
/// @ingroup event

class index_event : public event
{
public:
    /// Integral type
    typedef index_type size_type;

    index_event() : m_index(nindex) {}

    /// Returns index of the associated item in the container
    size_type index() const { return m_index; }

private:
    size_type m_index;

#ifndef DOXYGEN
    template <class NativeEvent, class UIEvent>
    friend class native::event_functor_event;
#endif
};

/// @brief Keyboard state class
/// @ingroup event

class keyboard_state
{
public:
    keyboard_state() : m_ctrl(false), m_shift(false), m_alt(false), m_meta(false) {}

    /// Returns true only if Control key is pressed
    bool ctrl() const { return m_ctrl; }

    /// Returns true only if Shift key is pressed
    bool shift() const { return m_shift; }

    /// Returns true only if Alt key is pressed
    bool alt() const { return m_alt; }

    /// Returns true only if Meta key is pressed
    bool meta() const { return m_meta; }

private:
    bool m_ctrl;
    bool m_shift;
    bool m_alt;
    bool m_meta;

#ifndef DOXYGEN
    template <class NativeEvent, class UIEvent>
    friend class native::event_functor_event;
#endif
};

/// @brief Keyboard event class
/// that holds information about keyboard when event was generated
/// @see <a href="http://en.wikipedia.org/wiki/Computer_keyboard">Keyboard (Wikipedia)</a>
/// @see <a href="http://www.w3.org/TR/DOM-Level-3-Events-key/">DOM Level 3 KeyboardEvent key Values (W3C)</a>
/// @ingroup event

class key_event : public event, public keyboard_state
{
public:
    key_event() : m_code(0), m_char(0) {}

    /// Returns associated key code
    int key_code() const { return m_code; }

    /// Returns associated character
#ifndef BOOST_NO_CXX11_CHAR32_T
    char32_t
#else
    int
#endif
    get_char() const { return m_char; }

private:
    int m_code;
    int m_char;

#ifndef DOXYGEN
    template <class NativeEvent, class UIEvent>
    friend class native::event_functor_event;
#endif
};

/// @brief Mouse event class
/// that holds information about mouse when event was generated
/// @see <a href="http://en.wikipedia.org/wiki/Mouse_(computing)">Mouse (Wikipedia)</a>
/// @ingroup event

class mouse_event : public event
{
public:
    mouse_event();

    /// Returns x mouse coordinate relative to the parent widget client area
    coord_type x() const { return m_x; }

    /// Returns y mouse coordinate relative to the parent widget client area
    coord_type y() const { return m_y; }

    /// Returns mouse position relative to the parent widget client area
    point pos() const { return point(x(), y()); }

    ///@{ Returns true if mouse button is pressed or was unpressed in this event
    bool left() const { return m_left; }
    bool right() const { return m_right; }
    bool middle() const { return m_middle; }
    ///@}

private:
    coord_type m_x;
    coord_type m_y;
    bool m_left;
    bool m_right;
    bool m_middle;

#ifndef DOXYGEN
    template <class NativeEvent, class UIEvent>
    friend class native::event_functor_event;
#endif
};

/// @brief Mouse wheel event class
/// @see <a href="http://en.wikipedia.org/wiki/Scroll_wheel">Scroll wheel (Wikipedia)</a>
/// @ingroup event
class wheel_event : public mouse_event
{
public:
    wheel_event() : m_horizontal(false), m_delta(0) {}

    /// Returns true only if wheel move is horizontal
    bool horizontal() const { return m_horizontal; }

    /// Returns true only if wheel move is vertical
    bool vertical() const { return !m_horizontal; }

    /// Returns wheel horizontal move delta
    coord_type delta_x() const { return horizontal() ? m_delta : 0; }

    /// Returns wheel vertical move delta
    coord_type delta_y() const { return vertical() ? m_delta : 0; }

private:
    bool m_horizontal;
    coord_type m_delta;

#ifndef DOXYGEN
    template <class NativeEvent, class UIEvent>
    friend class native::event_functor_event;
#endif
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_EVENT_HPP
