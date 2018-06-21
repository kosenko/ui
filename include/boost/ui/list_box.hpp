// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file list_box.hpp List box widget

#ifndef BOOST_UI_LIST_BOX_HPP
#define BOOST_UI_LIST_BOX_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/strings_box.hpp>

namespace boost {
namespace ui    {

/// @brief Widget to select one or more strings
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp list_box
/// @see <a href="http://en.wikipedia.org/wiki/List_box">List box (Wikipedia)</a>
/// @ingroup strings

class BOOST_UI_DECL list_box : public strings_box
{
public:
    list_box() {}

    ///@{ Creates empty list_box widget
    explicit list_box(widget& parent)
        { create(parent); }
    list_box& create(widget& parent);
    ///@}

    ///@{ Creates list_box widget with options
    explicit list_box(widget& parent, const std::vector<uistring>& options)
        { create(parent, options); }

    list_box& create(widget& parent, const std::vector<uistring>& options);

    template <class Iterator>
    explicit list_box(widget& parent, Iterator first, Iterator last)
        { create(parent, first, last); }

    template <class Iterator>
    list_box& create(widget& parent, Iterator first, Iterator last)
        { return create(parent, std::vector<uistring>(first, last)); }

    template <class Range>
    explicit list_box(widget& parent, const Range& r)
        { create(parent, r); }

    template <class Range>
    list_box& create(widget& parent, const Range& r)
        { return create(parent, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit list_box(widget& parent, std::initializer_list<T> list)
        { create(parent, list); }

    template <class T>
    list_box& create(widget& parent, std::initializer_list<T> list)
        { return create(parent, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    /// Returns true if list_box has selected options, false otherwise.
    bool has_selection() const
        { return selected_index() != npos; }

    /// Returns index of the selected option. If list_box has no selected options then returns @ref npos.
    size_type selected_index() const;

    /// Returns selected option string
    uistring selected_string() const;

    ///@{ Connects item selection handler
    BOOST_UI_DETAIL_HANDLER(select, list_box);
    BOOST_UI_DETAIL_HANDLER_EVENT(select_event, list_box, index_event);
    ///@}

    ///@{ Connects item activation handler
    BOOST_UI_DETAIL_HANDLER(activate, list_box);
    BOOST_UI_DETAIL_HANDLER_EVENT(activate_event, list_box, index_event);
    ///@}

private:
    void on_select_raw(const boost::function<void()>& handler);
    void on_select_event_raw(const boost::function<void(index_event&)>& handler);

    void on_activate_raw(const boost::function<void()>& handler);
    void on_activate_event_raw(const boost::function<void(index_event&)>& handler);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LIST_BOX_HPP
