// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file text_box.hpp @brief Text editor widgets

#ifndef BOOST_UI_TEXT_BOX_HPP
#define BOOST_UI_TEXT_BOX_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Abstract text editor widget
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp string_box
/// @ingroup text

class BOOST_UI_DECL text_box_base : public widget
{
public:
    /// Clears the contents
    void clear();

    /// Sets text into the editor
    text_box_base& text(const uistring& text);

    /// Returns text from the editor
    uistring text() const;

    ///@{ Connects text edit handler
    BOOST_UI_DETAIL_HANDLER(edit, text_box_base);
    ///@}

protected:
    text_box_base() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, const uistring& text, int style);
#endif

private:
    void on_edit_raw(const boost::function<void()>& handler);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

/// @brief Single-line text editor widget
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp string_box
/// @see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
/// @ingroup text

class BOOST_UI_DECL string_box : public text_box_base
{
public:
    string_box() {}

    ///@{ @brief Creates widget
    ///   @param parent Parent widget
    ///   @param text Initial text in the editor
    explicit string_box(widget& parent, const uistring& text = uistring())
        { create(parent, text); }
    string_box& create(widget& parent, const uistring& text = uistring());
    ///@}
};

/// @brief Password editor widget
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp string_box
/// @see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
/// @ingroup text

class BOOST_UI_DECL password_box : public text_box_base
{
public:
    password_box() {}

    ///@{ @brief Creates widget
    ///   @param parent Parent widget
    ///   @param text Initial text in the editor
    explicit password_box(widget& parent, const uistring& text = uistring())
        { create(parent, text); }
    password_box& create(widget& parent, const uistring& text = uistring());
    ///@}
};

/// @brief Multi-line text editor widget
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp string_box
/// @see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
/// @ingroup text

class BOOST_UI_DECL text_box : public text_box_base
{
public:
    text_box() {}

    ///@{ @brief Creates widget
    ///   @param parent Parent widget
    ///   @param text Initial text in the editor
    explicit text_box(widget& parent, const uistring& text = uistring())
        { create(parent, text); }
    text_box& create(widget& parent, const uistring& text = uistring());
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_TEXT_BOX_HPP
