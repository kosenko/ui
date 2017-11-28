// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file locale.hpp Localization

#ifndef BOOST_UI_LOCALE_HPP
#define BOOST_UI_LOCALE_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <locale>

namespace boost {
namespace ui    {

/// @brief Returns the current locale associated with the user interface
/// @ingroup locale
BOOST_UI_DECL std::locale getloc();

// @brief Replaces locale associated with the user interface
// @return The locale before the call of this function
// @ingroup locale
//std::locale imbue(const std::locale& loc);

} // namespace ui
} // namespace boost

#endif // BOOST_UI_LOCALE_HPP
