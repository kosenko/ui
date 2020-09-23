// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file thread.hpp @brief Thread support

#ifndef BOOST_UI_THREAD_HPP
#define BOOST_UI_THREAD_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/function.hpp>

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#include <boost/move/utility.hpp> // boost::forward()
#endif

namespace boost  {
namespace ui     {

#ifndef DOXYGEN

namespace detail {
BOOST_UI_DECL void call_async(const boost::function<void()>& fn);
} // namespace detail

#endif

/// @brief Calls @a f in the idle time in UI thread. This function is thread safe.
/// @see <a href="http://en.wikipedia.org/wiki/Thread_safety">Thread safety (Wikipedia)</a>
/// @ingroup thread

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <class F, class ...Args>
void call_async(F&& f, Args&&... args)
{
    detail::call_async(std::bind(boost::forward<F>(f), boost::forward<Args>(args)...));
}
#else
inline void call_async(const boost::function<void()>& fn)
{
    detail::call_async(fn);
}
#endif


} // namespace ui
} // namespace boost

#endif // BOOST_UI_THREAD_HPP
