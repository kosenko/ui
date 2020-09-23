// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file config.hpp @brief Configuration options

#ifndef BOOST_UI_CONFIG_HPP
#define BOOST_UI_CONFIG_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

//------------------------------------------------------------------------------

#ifndef DOXYGEN

#if (__cplusplus < 201103L || \
     defined(_MSC_VER) && _MSC_VER < 1600) /* Visual C++ 10 (2010)*/ \
     && ( (!defined __GLIBCXX__) || (__GLIBCXX__ > 20070719) )

#define BOOST_UI_NO_STD_HASH

#endif

//------------------------------------------------------------------------------
// normalize macros

#if defined(BOOST_UI_DYN_LINK) && defined(BOOST_UI_STATIC_LINK)
#   error Must not define both BOOST_UI_DYN_LINK and BOOST_UI_STATIC_LINK
#endif

//------------------------------------------------------------------------------
// dynamic linking

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_UI_DYN_LINK)
#   if defined(BOOST_UI_SOURCE)
#       define BOOST_UI_DECL BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_UI_DECL BOOST_SYMBOL_IMPORT
#   endif
#else
#   define BOOST_UI_DECL
#endif

//------------------------------------------------------------------------------
// auto-linking

#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_UI_NO_LIB) \
    && !defined(BOOST_UI_SOURCE)

#ifndef BOOST_LIB_NAME
#define BOOST_LIB_NAME boost_ui
#endif

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_UI_DYN_LINK)
#define BOOST_DYN_LINK
#endif

#include <boost/config/auto_link.hpp>

#if defined(_MSC_VER) && !defined(BOOST_UI_WXWIDGETS_NO_LIB)
#include <msvc/wx/setup.h> // In %WXWIN%\include\ folder
#ifdef BOOST_LIB_DIAGNOSTIC
#pragma message("Linking to wxWidgets")
#endif
#endif

#endif // auto-linking

#endif // !DOXYGEN

//------------------------------------------------------------------------------
// Doxygen

#ifdef DOXYGEN

/// @brief Enables Boost.Chrono library
/// @ingroup helper
#define BOOST_UI_USE_CHRONO

/// @brief Enables Boost.Date_Time library
/// @ingroup helper
#define BOOST_UI_USE_DATE_TIME

/// @brief Enables Boost.Filesystem library
/// @ingroup helper
#define BOOST_UI_USE_FILESYSTEM

#endif // DOXYGEN

#endif // BOOST_UI_CONFIG_HPP
