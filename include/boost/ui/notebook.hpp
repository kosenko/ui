// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file notebook.hpp @brief Notebook widget

#ifndef BOOST_UI_NOTEBOOK_HPP
#define BOOST_UI_NOTEBOOK_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that is an array of tabbed widgets
/// @see <a href="http://en.wikipedia.org/wiki/Tab_(GUI)">Tab (Wikipedia)</a>
/// @ingroup container

class BOOST_UI_DECL notebook : public widget
{
public:
    /// Unsigned integral type
    typedef index_type size_type;

    notebook() {}

    ///@{ Creates notebook widget
    explicit notebook(widget& parent)
        { create(parent); }
    notebook& create(widget& parent);
    ///@}

    /// Appends page with associated label
    void append_page(widget& page, const uistring& label);

    /// Shows page with @a index
    void current_page(size_type index);

    /// Returns index of the current page. If notebook has no pages then returns @ref npos
    size_type current_page_index() const;

    /// Invalid page index
    static const size_type npos = nindex;

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_NOTEBOOK_HPP
