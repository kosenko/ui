// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file status_bar.hpp @brief Status bar class

#ifndef BOOST_UI_STATUS_BAR_HPP
#define BOOST_UI_STATUS_BAR_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Status bar class
/// @details Default constructor is a private member, so use @ref boost::ui::frame::status_bar() to create this class instance
/// @see <a href="https://en.wikipedia.org/wiki/Status_bar">Status bar (Wikipedia)</a>
/// @ingroup info

class BOOST_UI_DECL status_bar
{
    status_bar();
    void create(widget& parent);

public:
    /// Copy constructor
    status_bar(const status_bar& other);
    ~status_bar();

    /// Sets text into the status bar
    status_bar& text(const uistring& text);

    /// Returns text from the status bar
    uistring text() const;

    /// Implementation-defined status bar type
    typedef void* native_handle_type;

    ///@{ Returns the implementation-defined underlying status bar handle
    native_handle_type native_handle() { return m_impl; }
    const native_handle_type native_handle() const { return m_impl; }
    ///@}

private:
    class native_impl;
    native_impl* m_impl;

#ifndef DOXYGEN
    friend class frame;
#endif
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_STATUS_BAR_HPP
