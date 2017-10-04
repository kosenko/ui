// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file listbox.hpp Listbox widget

#ifndef BOOST_UI_LISTBOX_HPP
#define BOOST_UI_LISTBOX_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/strings_box.hpp>

namespace boost {
namespace ui    {

/// @brief Widget to select one or more strings
/// @see <a href="http://en.wikipedia.org/wiki/List_box">List box (Wikipedia)</a>
/// @ingroup strings

class BOOST_UI_DECL listbox : public strings_box
{
public:
    listbox() {}

    ///@{ Creates empty listbox widget
    explicit listbox(widget& parent)
        { create(parent); }
    listbox& create(widget& parent);
    ///@}

    ///@{ Creates listbox widget with options
    explicit listbox(widget& parent, const std::vector<uistring>& options)
        { create(parent, options); }

    listbox& create(widget& parent, const std::vector<uistring>& options);

    template <class Iterator>
    explicit listbox(widget& parent, Iterator first, Iterator last)
        { create(parent, first, last); }

    template <class Iterator>
    listbox& create(widget& parent, Iterator first, Iterator last)
        { return create(parent, std::vector<uistring>(first, last)); }

    template <class Range>
    explicit listbox(widget& parent, const Range& r)
        { create(parent, r); }

    template <class Range>
    listbox& create(widget& parent, const Range& r)
        { return create(parent, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit listbox(widget& parent, std::initializer_list<T> list)
        { create(parent, list); }

    template <class T>
    listbox& create(widget& parent, std::initializer_list<T> list)
        { return create(parent, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    /// Returns true if listbox has selected options, false otherwise.
    bool has_selection() const
        { return selected_index() != npos; }

    /// Returns index of the selected option. If listbox has no selected options then returns @ref npos.
    size_type selected_index() const;

    /// Returns selected option string
    uistring selected_string() const;

    ///@{ Connects item selection handler
    listbox& on_select(const boost::function<void()>& handler);
    listbox& on_select_event(const boost::function<void(index_event&)>& handler);
    ///@}

    ///@{ Connects item activation handler
    listbox& on_activate(const boost::function<void()>& handler);
    listbox& on_activate_event(const boost::function<void(index_event&)>& handler);
    ///@}

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LISTBOX_HPP
