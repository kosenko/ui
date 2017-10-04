// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file combo_box.hpp Combo box widget

#ifndef BOOST_UI_COMBO_BOX_HPP
#define BOOST_UI_COMBO_BOX_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/stringsbox.hpp>

namespace boost {
namespace ui    {

/// @brief Widget to select one or more strings and edit it
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp combo_box
/// @see <a href="http://en.wikipedia.org/wiki/Combo_box">Combo box (Wikipedia)</a>
/// @ingroup strings

class BOOST_UI_DECL combo_box : public stringsbox
{
public:
    combo_box() {}

    ///@{ Creates empty combo box widget
    explicit combo_box(widget& parent)
        { create(parent); }

    combo_box& create(widget& parent);
    ///@}

    ///@{ Creates combo box widget without options and with initial text
    explicit combo_box(widget& parent, const uistring& text)
        { create(parent, text); }

    combo_box& create(widget& parent, const uistring& text)
        { return create(parent, text, std::vector<uistring>()); }
    ///@}

    ///@{ Creates combo box widget with options and without initial text
    explicit combo_box(widget& parent, const std::vector<uistring>& options)
        { create(parent, options); }

    combo_box& create(widget& parent, const std::vector<uistring>& options)
        { return create(parent, uistring(), options); }

    template <class Iterator>
    explicit combo_box(widget& parent, Iterator first, Iterator last)
        { create(parent, first, last); }

    template <class Iterator>
    combo_box& create(widget& parent, Iterator first, Iterator last)
        { return create(parent, std::vector<uistring>(first, last)); }

    template <class Range>
    explicit combo_box(widget& parent, const Range& r)
        { create(parent, r); }

    template <class Range>
    combo_box& create(widget& parent, const Range& r)
        { return create(parent, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit combo_box(widget& parent, std::initializer_list<T> list)
        { create(parent, list); }

    template <class T>
    combo_box& create(widget& parent, std::initializer_list<T> list)
        { return create(parent, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    ///@{ Creates combo_box widget with options and initial text
    explicit combo_box(widget& parent, const uistring& text,
                      const std::vector<uistring>& options)
        { create(parent, text, options); }

    combo_box& create(widget& parent, const uistring& text, const std::vector<uistring>& options);

    template <class Range>
    explicit combo_box(widget& parent, const uistring& text, const Range& r)
        { create(parent, text, r); }

    template <class Range>
    combo_box& create(widget& parent, const uistring& text, const Range& r)
        { return create(parent, text, detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    explicit combo_box(widget& parent, const uistring& text, std::initializer_list<T> list)
        { create(parent, text, list); }

    template <class T>
    combo_box& create(widget& parent, const uistring& text, std::initializer_list<T> list)
        { return create(parent, text, detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    /// Sets text into the editor
    combo_box& text(const uistring& txt);

    /// Returns text from the editor
    uistring text() const;

    ///@{ Connects item selection handler
    combo_box& on_select(const boost::function<void()>& handler);
    combo_box& on_select_event(const boost::function<void(index_event&)>& handler);
    ///@}

private:
    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_COMBO_BOX_HPP
