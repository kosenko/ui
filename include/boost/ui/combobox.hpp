// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file combobox.hpp Combobox widget

#ifndef BOOST_UI_COMBOBOX_HPP
#define BOOST_UI_COMBOBOX_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/stringsbox.hpp>

namespace boost {
namespace ui    {

/// @brief Widget to select one or more strings and edit it
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp combobox
/// @see <a href="http://en.wikipedia.org/wiki/Combo_box">Combo box (Wikipedia)</a>
/// @ingroup strings

class BOOST_UI_DECL combobox : public stringsbox
{
public:
    combobox() {}

    ///@{ Creates empty combobox widget
    explicit combobox(widget& parent)
        { create(parent); }

    combobox& create(widget& parent);
    ///@}

    ///@{ Creates combobox widget without options and with initial text
    explicit combobox(widget& parent, const uistring& text)
        { create(parent, text); }

    combobox& create(widget& parent, const uistring& text)
        { return create(parent, text, std::vector<uistring>()); }
    ///@}

    ///@{ Creates combobox widget with options and without initial text
    explicit combobox(widget& parent, const std::vector<uistring>& options)
        { create(parent, options); }

    combobox& create(widget& parent, const std::vector<uistring>& options)
        { return create(parent, uistring(), options); }

    template <class Iterator>
    explicit combobox(widget& parent, Iterator first, Iterator last)
        { create(parent, first, last); }

    template <class Iterator>
    combobox& create(widget& parent, Iterator first, Iterator last)
        { return create(parent, std::vector<uistring>(first, last)); }

    template <class Range>
    explicit combobox(widget& parent, const Range& r)
        { create(parent, r); }

    template <class Range>
    combobox& create(widget& parent, const Range& r)
        { return create(parent, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit combobox(widget& parent, std::initializer_list<T> list)
        { create(parent, list); }

    template <class T>
    combobox& create(widget& parent, std::initializer_list<T> list)
        { return create(parent, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    ///@{ Creates combobox widget with options and initial text
    explicit combobox(widget& parent, const uistring& text,
                      const std::vector<uistring>& options)
        { create(parent, text, options); }

    combobox& create(widget& parent, const uistring& text, const std::vector<uistring>& options);

    template <class Range>
    explicit combobox(widget& parent, const uistring& text, const Range& r)
        { create(parent, text, r); }

    template <class Range>
    combobox& create(widget& parent, const uistring& text, const Range& r)
        { return create(parent, text, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit combobox(widget& parent, const uistring& text, std::initializer_list<T> list)
        { create(parent, text, list); }

    template <class T>
    combobox& create(widget& parent, const uistring& text, std::initializer_list<T> list)
        { return create(parent, text, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    /// Sets text into the editor
    combobox& text(const uistring& txt);

    /// Returns text from the editor
    uistring text() const;

    ///@{ Connects item selection handler
    combobox& on_select(const boost::function<void()>& handler);
    combobox& on_select_event(const boost::function<void(index_event&)>& handler);
    ///@}

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COMBOBOX_HPP
