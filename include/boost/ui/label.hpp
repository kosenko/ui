// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file label.hpp Label widget

#ifndef BOOST_UI_LABEL_HPP
#define BOOST_UI_LABEL_HPP

#include <boost/ui/config.hpp>
#include <boost/ui/widget.hpp>

namespace boost {
namespace ui    {

/// @brief Widget that displays static text
/// @see <a href="http://en.wikipedia.org/wiki/Label_(control)">Label (Wikipedia)</a>
/// @ingroup info

class BOOST_UI_DECL label : public widget
{
public:
    label() { init(); }

    ///@{ Creates label widget with text
    explicit label(widget& parent, const uistring& txt = uistring())
        { init(); create(parent, txt); }
    explicit label(const uistring& txt)
        { init(); create(txt); }
    label& create(widget& parent, const uistring& txt = uistring());
    label& create(const uistring& txt = uistring())
        { text(txt); return *this; }
    ///@}

    /// Clears text
    void clear() { text(uistring()); }

    /// Sets text
    label& text(const uistring& txt);

    /// Returns text
    uistring text() const;

private:
    void init();

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LABEL_HPP
