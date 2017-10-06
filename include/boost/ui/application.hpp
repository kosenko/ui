// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file application.hpp Application class

#ifndef BOOST_UI_APPLICATION_HPP
#define BOOST_UI_APPLICATION_HPP

#include <boost/ui/config.hpp>

#ifndef BOOST_NO_CXX11_HDR_CHRONO
#include <chrono>
#endif

#include <boost/function.hpp>

#ifdef BOOST_UI_USE_CHRONO
#include <boost/chrono.hpp>
#endif

#ifdef BOOST_UI_USE_DATE_TIME
#include <boost/date_time/time_duration.hpp>
#endif

namespace boost {
namespace ui    {

///@{ @brief UI application entry
/// @details Initializes and uninitializer UI library, catches exceptions
/// @ingroup helper
/**
 * @param ui_main main UI function
 * @param argc count of program arguments
 * @param argv array of program arguments
 */
BOOST_UI_DECL int entry(int (*ui_main)(int, char*[]), int argc, char* argv[]);
BOOST_UI_DECL int entry(int (*ui_main)(),             int argc, char* argv[]);
///@}

#ifndef DOXYGEN

namespace detail {
BOOST_UI_DECL void on_timeout(int milliseconds, const boost::function<void()>& fn);
} // namespace detail

#endif

///@{ @brief Calls function one time after the specified time duration
/// @details
/// Usage example:
/// @snippet cpp11/snippet.cpp on_timeout
/// @see BOOST_UI_USE_CHRONO
/// @see BOOST_UI_USE_DATE_TIME
/// @see <a href="http://en.wikipedia.org/wiki/Timeout_(computing)">Timeout (Wikipedia)</a>
/// @see <a href="http://en.wikipedia.org/wiki/Timer">Timer (Wikipedia)</a>
/// @ingroup event

#ifndef BOOST_NO_CXX11_HDR_CHRONO
template <class Rep, class Period>
void on_timeout(const std::chrono::duration<Rep, Period>& d,
                const boost::function<void()>& fn)
{
    detail::on_timeout(static_cast<int>(std::chrono::duration_cast<
                           std::chrono::milliseconds>(d).count()),
                       fn);
}
#endif

#ifdef BOOST_UI_USE_CHRONO
template <class Rep, class Period>
void on_timeout(const boost::chrono::duration<Rep, Period>& d,
                const boost::function<void()>& fn)
{
    detail::on_timeout(static_cast<int>(boost::chrono::duration_cast<
                           boost::chrono::milliseconds>(d).count()),
                       fn);
}
#endif

#ifdef BOOST_UI_USE_DATE_TIME
template <class T, typename rep_type>
void on_timeout(const boost::date_time::time_duration<T, rep_type>& td,
                const boost::function<void()>& fn)
{
    detail::on_timeout(static_cast<int>( td.total_milliseconds() ), fn);
}
#endif

///@}

#ifndef DOXYGEN

namespace detail {
BOOST_UI_DECL void sleep_for_milliseconds(unsigned long milliseconds);
BOOST_UI_DECL void sleep_for_microseconds(unsigned long microseconds);
} // namespace detail

///@{ @brief std::this_thread::sleep_for() that doesn't require Boost.Thread library
/// @see BOOST_UI_USE_CHRONO
/// @see BOOST_UI_USE_DATE_TIME
/// @ingroup helper

#ifndef BOOST_NO_CXX11_HDR_CHRONO
template <class Rep, class Period>
void sleep_for(const std::chrono::duration<Rep, Period>& d)
{
    const unsigned long milliseconds = static_cast<unsigned long>(
        std::chrono::duration_cast<std::chrono::milliseconds>(d).count());
    if ( milliseconds > 1000 )
        detail::sleep_for_milliseconds(milliseconds);
    else
        detail::sleep_for_microseconds(static_cast<unsigned long>(
            std::chrono::duration_cast<std::chrono::microseconds>(d).count() ));
}
#endif

#ifdef BOOST_UI_USE_CHRONO
template <class Rep, class Period>
void sleep_for(const boost::chrono::duration<Rep, Period>& d)
{
    const unsigned long milliseconds = static_cast<unsigned long>(
        boost::chrono::duration_cast<boost::chrono::milliseconds>(d).count());
    if ( milliseconds > 1000 )
        detail::sleep_for_milliseconds(milliseconds);
    else
        detail::sleep_for_microseconds(static_cast<unsigned long>(
            boost::chrono::duration_cast<boost::chrono::microseconds>(d).count() ));
}
#endif

#ifdef BOOST_UI_USE_DATE_TIME
template <class T, typename rep_type>
void sleep_for(const boost::date_time::time_duration<T, rep_type>& td)
{
    const unsigned long milliseconds = static_cast<unsigned long>(td.total_milliseconds());
    if ( milliseconds > 1000 )
        detail::sleep_for_milliseconds(milliseconds);
    else
        detail::sleep_for_microseconds(static_cast<unsigned long>( td.total_microseconds() ));
}
#endif

///@}

#endif // !DOXYGEN

#ifndef DOXYGEN
namespace detail {
BOOST_UI_DECL void assertion_failed_msg(char const* expr, char const* msg,
                                        char const* function,
                                        char const* file, long line);
} // namespace detail
#endif

} // namespace ui

#ifndef DOXYGEN
inline void assertion_failed_msg(char const* expr, char const* msg,
                                 char const* function,
                                 char const* file, long line)
{
    ui::detail::assertion_failed_msg(expr, msg, function, file, line);
}

inline void assertion_failed(char const* expr,
                             char const* function,
                             char const* file, long line)
{
    assertion_failed_msg(expr, NULL, function, file, line);
}
#endif

} // namespace boost

#endif // BOOST_UI_APPLICATION_HPP
