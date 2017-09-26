// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file checkbox.hpp Checkbox widget

#ifndef BOOST_UI_CHECKBOX_HPP
#define BOOST_UI_CHECKBOX_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/def.hpp>
#include <boost/ui/widget.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace ui    {

/// @brief Checkbox base class
/// @ingroup io

class BOOST_UI_DECL checkbox_base : public widget
{
public:
    ///@{ Sets checkbox state
    checkbox_base& check(nullopt_t) { indeterminate(); return *this; }
    checkbox_base& check(bool checked = true);
    checkbox_base& uncheck() { return check(false); }
    checkbox_base& indeterminate();
    checkbox_base& tribool(boost::tribool value)
    {
        if ( value ) check();
        else if ( !value ) uncheck();
        else indeterminate();
        return *this;
    }
    checkbox_base& optional(boost::optional<bool> value)
    {
        if ( !value ) indeterminate();
        else if ( *value ) check();
        else uncheck();
        return *this;
    }
    ///@}

    ///@{ Returns checkbox state
    bool is_checked() const;
    bool is_unchecked() const;
    bool is_indeterminate() const;
    boost::tribool tribool() const
    {
        return is_checked() ? boost::tribool(true)
                            : is_unchecked() ? boost::tribool(false)
                                             : boost::indeterminate;
    }
    boost::optional<bool> optional() const
    {
        return is_checked() ? boost::optional<bool>(true)
                            : is_unchecked() ? boost::optional<bool>(false)
                                             : boost::none;
    }
    ///@}

    /// Connects checkbox toggle handler
    checkbox_base& on_toggle(const boost::function<void()>& handler);

protected:
    checkbox_base() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, const uistring& text, bool istristate);
#endif

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

/// @brief Labelled widget that that permits the user to make a binary choice
/// @see <a href="http://en.wikipedia.org/wiki/Checkbox">Checkbox (Wikipedia)</a>
/// @ingroup io

class BOOST_UI_DECL checkbox : public checkbox_base
{
public:
    checkbox() {}

    ///@{ Creates checkbox widget with text
    explicit checkbox(widget& parent, const uistring& text)
        { create(parent, text); }
    checkbox& create(widget& parent, const uistring& text)
        { detail_create(parent, text, false); return *this; }
    ///@}
};

/// @brief Labelled widget that that permits the user to make a ternary choice
/// @see <a href="http://en.wikipedia.org/wiki/Checkbox">Checkbox (Wikipedia)</a>
/// @ingroup io

class BOOST_UI_DECL tristate_checkbox : public checkbox_base
{
public:
    tristate_checkbox() {}

    ///@{ Creates tristate checkbox widget with text
    explicit tristate_checkbox(widget& parent, const uistring& text)
        { create(parent, text); }
    tristate_checkbox& create(widget& parent, const uistring& text)
        { detail_create(parent, text, true); return *this; }
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_CHECKBOX_HPP
