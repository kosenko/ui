// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file menu.hpp Menu classes

#ifndef BOOST_UI_MENU_HPP
#define BOOST_UI_MENU_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

#include <boost/noncopyable.hpp>

namespace boost {
namespace ui    {

/// @brief List of selected items
/// @see <a href="http://en.wikipedia.org/wiki/Menu_(computing)">Menu (Wikipedia)</a>
/// @ingroup command

class BOOST_UI_DECL menu : private boost::noncopyable
{
public:
    class item;

    menu();
    ~menu();

    ///@{ @brief Appends subitem
    menu& append(const item& i);
    menu& operator<<(const item& i)
        { return append(i); }
    ///@}

    /// Popups context menu
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
};

/// @brief Menu item
/// @ingroup command

class BOOST_UI_DECL menu::item : private boost::noncopyable
{
public:
    /// Constructs menu item with text
    item(const uistring& text);

    /// Implementation-defined men item type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying menu item handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    class native_impl;
    native_impl* m_impl;

#ifndef DOXYGEN
    friend class menu;
#endif
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_MENU_HPP
