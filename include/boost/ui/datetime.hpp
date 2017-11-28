// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file datetime.hpp Date and time pickers

#ifndef BOOST_UI_DATETIME_HPP
#define BOOST_UI_DATETIME_HPP

#ifdef DOXYGEN
#define BOOST_UI_USE_DATE_TIME
#define BOOST_UI_USE_CHRONO
#endif

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>
#include <boost/cstdint.hpp>

#ifdef BOOST_UI_USE_DATE_TIME
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#endif

#ifdef BOOST_UI_USE_CHRONO
#include <boost/chrono.hpp>
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
#include <chrono>
#endif

#include <ctime>

namespace boost {
namespace ui    {

/// @brief Date picker widget
/// @see <a href="http://en.wikipedia.org/wiki/Calendar_date">Calendar date (Wikipedia)</a>
/// @ingroup datetime

class BOOST_UI_DECL date_picker : public widget
{
public:
    date_picker() {}

    ///@{ @brief Creates widget
    explicit date_picker(widget& parent)
        { create(parent); }
    date_picker& create(widget& parent);
    ///@}

    /// @brief Returns date in std::time_t format
    /// @throw std::out_of_range If selected date is not compatible with std::time_t format
    std::time_t get_time_t() const;

    /// @brief Sets date in std::time_t format
    /// @throw std::out_of_range If requested date is invalid
    date_picker& set_time_t(std::time_t t);

    /// @brief Returns local date in std::tm format
    /// @throw std::out_of_range If selected date is not compatible with std::tm format
    std::tm get_tm() const;

    /// @brief Sets local date in std::tm format
    /// @throw std::out_of_range If requested date is invalid
    date_picker& set_tm(const std::tm& t);

#ifdef BOOST_UI_USE_DATE_TIME
    /// @brief Returns boost::gregorian::date
    /// @throw std::out_of_range If date is out of range
    /// @see BOOST_UI_USE_DATE_TIME
    boost::gregorian::date gregorian_date() const
    {
        int year = 0, month = 0, day = 0;
        ymd(year, month, day);
        return boost::gregorian::date(year, month, day);
    }

    /// @brief Sets boost::gregorian::date
    /// @throw std::out_of_range If requested date is invalid
    /// @see BOOST_UI_USE_DATE_TIME
    date_picker& gregorian_date(const boost::gregorian::date& d)
    {
        set_ymd(d.year(), d.month(), d.day());
        return *this;
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    /// @brief Returns std::chrono::system_clock::time_point
    /// @throw std::out_of_range If date is out of range
    std::chrono::system_clock::time_point system_clock_time_point() const
    {
        return std::chrono::system_clock::from_time_t(get_time_t());
    }

    /// @brief Sets std::chrono::system_clock::time_point
    /// @throw std::out_of_range If requested date is invalid
    date_picker& system_clock_time_point(const std::chrono::system_clock::time_point& d)
    {
        set_time_t(std::chrono::system_clock::to_time_t(d));
        return *this;
    }
#endif

#ifdef BOOST_UI_USE_CHRONO
    /// @brief Returns boost::chrono::system_clock::time_point
    /// @throw std::out_of_range If date is out of range
    /// @see BOOST_UI_USE_CHRONO
    boost::chrono::system_clock::time_point boost_system_clock_time_point() const
    {
        return boost::chrono::system_clock::from_time_t(get_time_t());
    }

    /// @brief Sets boost::chrono::system_clock::time_point
    /// @throw std::out_of_range If requested date is invalid
    /// @see BOOST_UI_USE_CHRONO
    date_picker& system_clock_time_point(const boost::chrono::system_clock::time_point& d)
    {
        set_time_t(boost::chrono::system_clock::to_time_t(d));
        return *this;
    }
#endif

    /// Connects data change handler
    date_picker& on_change(const boost::function<void()>& handler);

#ifndef DOXYGEN
private:
    void ymd(int& year, int& month, int& day) const;
    void set_ymd(int year, int month, int day);

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
#endif
};

/// @brief Time picker widget
/// @details Works with time in range [0 hours, 24 hours)
/// @ingroup datetime

class BOOST_UI_DECL time_picker : public widget
{
public:
    time_picker() {}

    ///@{ @brief Creates widget
    explicit time_picker(widget& parent)
        { create(parent); }
    time_picker& create(widget& parent);
    ///@}

    /// @brief Returns count of seconds since midnight in std::time_t format
    /// @throw std::out_of_range If selected time is not compatible with std::time_t format
    std::time_t get_time_t() const;

    /// @brief Sets time in std::time_t format
    /// @throw std::out_of_range If requested time is invalid
    time_picker& set_time_t(std::time_t t);

    /// @brief Returns local time in std::tm format at epoch start day (1900-01-01)
    /// @throw std::out_of_range If selected time is not compatible with std::tm format
    std::tm get_tm() const;

    /// @brief Sets local time in std::tm format
    /// @throw std::out_of_range If requested time is invalid
    time_picker& set_tm(const std::tm& t);

#ifdef BOOST_UI_USE_DATE_TIME
    /// @brief Returns boost::posix_time::time_duration
    /// @throw std::out_of_range If time is out of range
    /// @see BOOST_UI_USE_DATE_TIME
    boost::posix_time::time_duration posix_time_duration() const
    {
        int hours = 0, minutes = 0, seconds = 0;
        get_time_raw(&hours, &minutes, &seconds);
        return boost::posix_time::time_duration(hours, minutes, seconds);
    }

    /// @brief Sets boost::posix_time::time_duration
    /// @throw std::out_of_range If requested time is invalid
    /// @see BOOST_UI_USE_DATE_TIME
    time_picker& posix_time_duration(const boost::posix_time::time_duration& d)
    {
        set_time(d.hours(), d.minutes(), d.seconds());
        return *this;
    }
#endif

#ifdef BOOST_UI_USE_CHRONO
    /// @brief Returns boost::chrono::duration
    /// @throw std::out_of_range If time is out of range
    /// @see BOOST_UI_USE_CHRONO
    template <class Rep, class Period>
    boost::chrono::duration<Rep, Period> boost_chrono_duration() const
    {
        return boost::chrono::seconds(get_seconds());
    }

    /// @brief Sets boost::chrono::duration
    /// @throw std::out_of_range If requested time is invalid
    /// @see BOOST_UI_USE_CHRONO
    template <class Rep, class Period>
    time_picker& chrono_duration(const boost::chrono::duration<Rep, Period>& d)
    {
        set_seconds(boost::chrono::duration_cast<boost::chrono::seconds>(d).count());
        return *this;
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_CHRONO
    /// @brief Returns std::chrono::duration
    /// @throw std::out_of_range If time is out of range
    template <class Rep, class Period>
    std::chrono::duration<Rep, Period> chrono_duration() const
    {
        return std::chrono::seconds(get_seconds());
    }

    /// @brief Sets std::chrono::duration
    /// @throw std::out_of_range If requested time is invalid
    template <class Rep, class Period>
    time_picker& chrono_duration(const std::chrono::duration<Rep, Period>& d)
    {
        set_seconds(std::chrono::duration_cast<std::chrono::seconds>(d).count());
        return *this;
    }
#endif

    /// @brief Returns time
    template <class T>
    void get_time(T hours_ptr, T minutes_ptr, T seconds_ptr)
    {
        int hours = 0;
        int minutes = 0;
        int seconds = 0;
        get_time_raw(&hours, &minutes, &seconds);
        if ( hours_ptr )
            *hours_ptr = hours;
        if ( minutes_ptr )
            *minutes_ptr = minutes;
        if ( seconds_ptr )
            *seconds_ptr = seconds;
    }

    /// @brief Sets time
    /// @throw std::out_of_range If time is out of range
    time_picker& set_time(int hours, int minutes, int seconds);

    /// Connects time change handler
    time_picker& on_change(const boost::function<void()>& handler);

private:
    void get_time_raw(int* hours_ptr, int* minutes_ptr, int* seconds_ptr) const;
    int get_seconds() const
    {
        int hours = 0, minutes = 0, seconds = 0;
        get_time_raw(&hours, &minutes, &seconds);
        return (hours * 60 + minutes) * 60 + seconds;
    }
    void set_seconds(boost::intmax_t seconds)
    {
        set_time(static_cast<int>(seconds / 3600), (seconds / 60) % 60, seconds % 60);
    }

    class detail_impl;
    detail_impl* get_impl();
    const detail_impl* get_impl() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_DATETIME_HPP
