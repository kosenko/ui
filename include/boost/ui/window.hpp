// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file window.hpp Window class

#ifndef BOOST_UI_WINDOW_HPP
#define BOOST_UI_WINDOW_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Close event class
/// @ingroup event

class close_event : public event
{
public:
    close_event() : m_veto(false) {}
    ~close_event();

    /// Don't close application
    void veto() { m_veto = true; }

private:
    bool m_veto;
    boost::function<void(bool)> m_veto_fn;
    boost::function<void(bool)> m_skip_fn;

#ifndef DOXYGEN
    template <class NativeEvent, class UIEvent>
    friend class native::event_functor_event;
#endif
};

/// @brief Abstract top level widget that hosts other widgets
/// @see <a href="http://en.wikipedia.org/wiki/Window_(computing)">Window (Wikipedia)</a>
/// @ingroup container

class BOOST_UI_DECL window : public widget
{
public:
    /// @brief Sets title
    /// @see <a href="http://en.wikipedia.org/wiki/Title_bar">Title bar (Wikipedia)</a>
    void title(const uistring& title);

    /// Returns title
    uistring title() const;

    /// @brief Shows an application-modal dialog
    /// @see <a href="http://en.wikipedia.org/wiki/Modal_window">Modal window (Wikipedia)</a>
    void show_modal();

    /// Initiates window close. Returns false if operation was vetoed
    bool close();

    ///@{ Connects window close handler
    window& on_close(const boost::function<void()>& handler);
    window& on_close_event(const boost::function<void(close_event&)>& handler);
    ///@}
};
} // namespace ui
} // namespace boost

#endif // BOOST_UI_WINDOW_HPP
