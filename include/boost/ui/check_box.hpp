// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file check_box.hpp Check box widget

#ifndef BOOST_UI_CHECK_BOX_HPP
#define BOOST_UI_CHECK_BOX_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/def.hpp>
#include <boost/ui/widget.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace ui    {

/// @brief Check box base class
/// @ingroup io

class BOOST_UI_DECL check_box_base : public widget
{
public:
    ///@{ Sets check box state
    check_box_base& check(nullopt_t) { indeterminate(); return *this; }
    check_box_base& check(bool checked = true);
    check_box_base& uncheck() { return check(false); }
    check_box_base& indeterminate();
    check_box_base& tribool(boost::tribool value)
    {
        if ( value ) check();
        else if ( !value ) uncheck();
        else indeterminate();
        return *this;
    }
    check_box_base& optional(boost::optional<bool> value)
    {
        if ( !value ) indeterminate();
        else if ( *value ) check();
        else uncheck();
        return *this;
    }
    ///@}

    ///@{ Returns check box state
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

    /// Connects check box toggle handler
    BOOST_UI_DETAIL_HANDLER(toggle, check_box_base);

protected:
    check_box_base() {}

#ifndef DOXYGEN
    void detail_create(widget& parent, const uistring& text, bool is_tri_state);
#endif

private:
    void on_toggle_raw(const boost::function<void()>& handler);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

/// @brief Labelled widget that that permits the user to make a binary choice
/// @see <a href="http://en.wikipedia.org/wiki/Checkbox">Checkbox (Wikipedia)</a>
/// @ingroup io

class BOOST_UI_DECL check_box : public check_box_base
{
public:
    check_box() {}

    ///@{ Creates check box widget with text
    explicit check_box(widget& parent, const uistring& text)
        { create(parent, text); }
    check_box& create(widget& parent, const uistring& text)
        { detail_create(parent, text, false); return *this; }
    ///@}
};

/// @brief Labelled widget that that permits the user to make a ternary choice
/// @see <a href="http://en.wikipedia.org/wiki/Checkbox">Checkbox (Wikipedia)</a>
/// @ingroup io

class BOOST_UI_DECL tri_state_check_box : public check_box_base
{
public:
    tri_state_check_box() {}

    ///@{ Creates tri-state check box widget with text
    explicit tri_state_check_box(widget& parent, const uistring& text)
        { create(parent, text); }
    tri_state_check_box& create(widget& parent, const uistring& text)
        { detail_create(parent, text, true); return *this; }
    ///@}
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_CHECK_BOX_HPP
