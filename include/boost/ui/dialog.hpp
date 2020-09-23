// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file dialog.hpp @brief Dialog widget

#ifndef BOOST_UI_DIALOG_HPP
#define BOOST_UI_DIALOG_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/window.hpp>

namespace boost {
namespace ui    {

/// @brief Top level widget that hosts other widgets
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp dialog
/// @see <a href="http://en.wikipedia.org/wiki/Dialog_box">Dialog (Wikipedia)</a>
/// @ingroup tlw

class BOOST_UI_DECL dialog : public window
{
public:
    dialog() {}

    ///@{ Creates dialog with the title
    explicit dialog(const uistring& title)
        { create(title); }
    dialog& create(const uistring& title);
    ///@}

private:
    class detail_impl;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_DIALOG_HPP
