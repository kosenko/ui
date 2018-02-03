// Copyright (c) 2017, 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file menu.hpp Menu classes

#ifndef BOOST_UI_MENU_HPP
#define BOOST_UI_MENU_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>
#include <boost/ui/detail/shared_count.hpp>
#include <boost/ui/detail/event.hpp>

#include <boost/noncopyable.hpp>

namespace boost {
namespace ui    {

/// @brief Pseudo class that separates menu items
/// @ingroup info

class BOOST_UI_DECL separator
{
};

class frame;
class menu;

/// @brief Menu bar class
/// @details Default constructor is a private member, so use @ref boost::ui::frame::menu_bar() to create this class instance
/// @see <a href="https://en.wikipedia.org/wiki/Menu_bar">Menu bar (Wikipedia)</a>
/// @ingroup command

class BOOST_UI_DECL menu_bar
{
    menu_bar();
    void create();

public:
    /// Copy constructor
    menu_bar(const menu_bar& other);
    ~menu_bar();

    ///@{ @brief Appends menu as subitem
    menu_bar& append(const menu& i);
    menu_bar& operator<<(const menu& i)
        { return append(i); }
    ///@}

    /// Implementation-defined menu bar type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying menu bar handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    class native_impl;
    native_impl* m_impl;

#ifndef DOXYGEN
    friend class frame;
    friend class menu;
#endif
};

/// @brief Menu (list of commands) class
/// @see <a href="http://en.wikipedia.org/wiki/Menu_(computing)">Menu (Wikipedia)</a>
/// @ingroup command

class BOOST_UI_DECL menu
{
public:
    class item;

    menu();
    ~menu();

    /// @brief Constructs menu with associated text label with mnemonics
    /// @see <a href="https://en.wikipedia.org/wiki/Mnemonics_(keyboard)">Mnemonics (Wikipedia)</a>
    menu(const uistring& text);

    ///@{ @brief Appends menu item as subitem
    menu& append(const item& i);
    menu& operator<<(const item& i)
        { return append(i); }
    ///@}

    ///@{ @brief Appends menu as subitem
    menu& append(const menu& i);
    menu& operator<<(const menu& i)
        { return append(i); }
    ///@}

    ///@{ @brief Appends separator
    menu& append(const separator& i);
    menu& operator<<(const separator& i)
        { return append(i); }
    ///@}

    /// @brief Popups context menu at current mouse postion related to widget @a w
    /// @see <a href="http://en.wikipedia.org/wiki/Context_menu">Context menu (Wikipedia)</a>
    /// @see <a href="http://en.wikipedia.org/wiki/Modal_window">Modal window (Wikipedia)</a>
    void popup(widget& w);

    /// Implementation-defined menu type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying menu handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    class native_impl;
    native_impl* m_impl;

    mutable detail::shared_count m_shared_count;

#ifndef DOXYGEN
    friend class menu_bar::native_impl;
#endif
};

/// @brief Menu item
/// @ingroup command

class BOOST_UI_DECL menu::item : private boost::noncopyable
{
public:
    /// @brief Constructs menu item with associated text label with mnemonics
    /// @see <a href="https://en.wikipedia.org/wiki/Mnemonics_(keyboard)">Mnemonics (Wikipedia)</a>
    item(const uistring& text);

    /// Connects menu item press handler
    BOOST_UI_DETAIL_HANDLER(press, item);

    /// Implementation-defined menu item type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying menu item handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    void on_press_raw(const boost::function<void()>& handler);

    class native_impl;
    native_impl* m_impl;

#ifndef DOXYGEN
    friend class menu;
#endif
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_MENU_HPP
