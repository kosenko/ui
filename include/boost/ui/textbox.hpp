// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file textbox.hpp Text editor widgets

#ifndef BOOST_UI_TEXTBOX_HPP
#define BOOST_UI_TEXTBOX_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Abstract text editor widget
/// @ingroup text

class BOOST_UI_DECL textbox_base : public widget
{
public:
    /// Clears the contents
    void clear();

    /// Sets text into the editor
    textbox_base& text(const uistring& text);

    /// Returns text from the editor
    uistring text() const;

    ///@{ Connects text edit handler
    textbox_base& on_edit(const boost::function<void()>& handler);
    ///@}

protected:
    textbox_base() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, const uistring& text, int style);
#endif

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

/// @brief Single-line text editor widget
/// @see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
/// @ingroup text

class BOOST_UI_DECL stringbox : public textbox_base
{
public:
    stringbox() {}

    ///@{ @brief Creates widget
    ///   @param parent Parent widget
    ///   @param text Initial text in the editor
    explicit stringbox(widget& parent, const uistring& text = uistring())
        { create(parent, text); }
    stringbox& create(widget& parent, const uistring& text = uistring());
    ///@}
};

/// @brief Password editor widget
/// @see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
/// @ingroup text

class BOOST_UI_DECL passwordbox : public textbox_base
{
public:
    passwordbox() {}

    ///@{ @brief Creates widget
    ///   @param parent Parent widget
    ///   @param text Initial text in the editor
    explicit passwordbox(widget& parent, const uistring& text = uistring())
        { create(parent, text); }
    passwordbox& create(widget& parent, const uistring& text = uistring());
    ///@}
};

/// @brief Multi-line text editor widget
/// @see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
/// @ingroup text

class BOOST_UI_DECL textbox : public textbox_base
{
public:
    textbox() {}

    ///@{ @brief Creates widget
    ///   @param parent Parent widget
    ///   @param text Initial text in the editor
    explicit textbox(widget& parent, const uistring& text = uistring())
        { create(parent, text); }
    textbox& create(widget& parent, const uistring& text = uistring());
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_TEXTBOX_HPP
