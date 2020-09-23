// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file choice.hpp @brief Choice widget

#ifndef BOOST_UI_CHOICE_HPP
#define BOOST_UI_CHOICE_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/strings_box.hpp>

namespace boost {
namespace ui    {

/// @brief Widget to select string from popup list of strings
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp choice
/// @see <a href="http://en.wikipedia.org/wiki/Drop-down_list">Drop-down list (Wikipedia)</a>
/// @ingroup strings

class BOOST_UI_DECL choice : public strings_box
{
public:
    choice() {}

    ///@{ Creates empty choice widget
    explicit choice(widget& parent)
        { create(parent); }
    choice& create(widget& parent);
    ///@}

    ///@{ Creates choice widget with options
    explicit choice(widget& parent, const std::vector<uistring>& options)
        { create(parent, options); }

    choice& create(widget& parent, const std::vector<uistring>& options);

    template <class Iterator>
    explicit choice(widget& parent, Iterator first, Iterator last)
        { create(parent, first, last); }

    template <class Iterator>
    choice& create(widget& parent, Iterator first, Iterator last)
        { return create(parent, std::vector<uistring>(first, last)); }

    template <class Range>
    explicit choice(widget& parent, const Range& r)
        { create(parent, r); }

    template <class Range>
    choice& create(widget& parent, const Range& r)
        { return create(parent, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit choice(widget& parent, std::initializer_list<T> list)
        { create(parent, list); }

    template <class T>
    choice& create(widget& parent, std::initializer_list<T> list)
        { return create(parent, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    /// Returns text that is associated this widget
    uistring text() const;

    /// Returns index of the selected text item. If widget has no items then returns @ref npos
    index_type current_selection_index() const;

    ///@{ Connects item selection handler
    BOOST_UI_DETAIL_HANDLER(select, choice);
    BOOST_UI_DETAIL_HANDLER_EVENT(select_event, choice, index_event);
    ///@}

private:
    void on_select_raw(const boost::function<void()>& handler);
    void on_select_event_raw(const boost::function<void(index_event&)>& handler);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_CHOICE_HPP
