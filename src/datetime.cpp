// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/native/config.hpp>

#include <boost/ui/datetime.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/dateevt.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>

namespace boost {
namespace ui    {

#if wxUSE_DATEPICKCTRL

class date_picker::detail_impl : public detail::widget_detail<wxDatePickerCtrl>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(new wxDatePickerCtrl(native::from_widget(parent), wxID_ANY));
    }
    wxDateTime GetValue() const
    {
        wxCHECK(m_native, wxDateTime());
        return m_native->GetValue();
    }
    void SetValue(const wxDateTime& datetime)
    {
        wxCHECK(m_native, );
        m_native->SetValue(datetime);
    }
};

#endif

date_picker::detail_impl* date_picker::get_impl()
{
#if wxUSE_DATEPICKCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const date_picker::detail_impl* date_picker::get_impl() const
{
#if wxUSE_DATEPICKCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

date_picker& date_picker::create(widget& parent)
{
#if wxUSE_DATEPICKCTRL
    detail_set_detail_impl(new detail_impl(parent));
#endif

    return *this;
}

std::time_t date_picker::get_time_t() const
{
#if wxUSE_DATEPICKCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, static_cast<std::time_t>(-1));

    const std::time_t result = impl->GetValue().GetTicks();
    if ( result == -1 )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::date_picker::get_time_t(): invalid std::time_t date"));

    return result;
#else
    return static_cast<std::time_t>(-1);
#endif
}

date_picker& date_picker::set_time_t(std::time_t t)
{
#if wxUSE_DATEPICKCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    const wxDateTime datetime(t);
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::date_picker::set_time_t(): invalid std::time_t date"));

    impl->SetValue(datetime);
#endif

    return *this;
}

std::tm date_picker::get_tm() const
{
#if wxUSE_DATEPICKCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, std::tm());

    const wxDateTime datetime = impl->GetValue();
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::date_picker::get_tm(): invalid datetime value"));

    wxDateTime::Tm t = datetime.GetTm();

    struct std::tm result;
    result.tm_year  = t.year - 1900;
    result.tm_mon   = t.mon;
    result.tm_mday  = t.mday;
    result.tm_hour  = t.hour;
    result.tm_min   = t.min;
    result.tm_sec   = t.sec;
    result.tm_yday  = t.yday;
    result.tm_isdst = -1;

    result.tm_wday  = t.GetWeekDay();

    return result;
#else
    return std::tm();
#endif
}

date_picker& date_picker::set_tm(const std::tm& t)
{
#if wxUSE_DATEPICKCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    const wxDateTime datetime(t);
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::date_picker::set_tm(): invalid std::tm date"));

    impl->SetValue(datetime);
#endif

    return *this;
}

void date_picker::ymd(int& year, int& month, int& day) const
{
#if wxUSE_DATEPICKCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, );

    const wxDateTime datetime = impl->GetValue();
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::date_picker::ymd(): invalid datetime value"));

    year  = datetime.GetYear();
    month = datetime.GetMonth() + 1;
    day   = datetime.GetDay();
#endif
}

void date_picker::set_ymd(int year, int month, int day)
{
#if wxUSE_DATEPICKCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, );

    const wxDateTime datetime(day, static_cast<wxDateTime::Month>(month - 1), year);
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::date_picker::set_ymd(): invalid date"));

    impl->SetValue(datetime);
#endif
}

void date_picker::on_change_raw(const boost::function<void()>& handler)
{
#if wxUSE_DATEPICKCTRL
    native::bind_helper(*this, wxEVT_DATE_CHANGED, handler);
#endif
}

//-----------------------------------------------------------------------------

#if wxUSE_TIMEPICKCTRL

class time_picker::detail_impl : public detail::widget_detail<wxTimePickerCtrl>
{
public:
    explicit detail_impl(widget& parent)
    {
        set_native_handle(new wxTimePickerCtrl(native::from_widget(parent), wxID_ANY));
    }
    wxDateTime GetValue() const
    {
        wxCHECK(m_native, wxDateTime());
        return m_native->GetValue();
    }
    void SetValue(const wxDateTime& datetime)
    {
        wxCHECK(m_native, );
        m_native->SetValue(datetime);
    }
    bool SetTime(int hour, int min, int sec)
    {
        wxCHECK(m_native, false);
        return m_native->SetTime(hour, min, sec);
    }
    bool GetTime(int* hour, int* min, int* sec) const
    {
        wxCHECK(m_native, false);
        return m_native->GetTime(hour, min, sec);
    }
};

#endif

time_picker::detail_impl* time_picker::get_impl()
{
#if wxUSE_TIMEPICKCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

const time_picker::detail_impl* time_picker::get_impl() const
{
#if wxUSE_TIMEPICKCTRL
    return get_detail_impl<detail_impl>();
#else
    return NULL;
#endif
}

time_picker& time_picker::create(widget& parent)
{
#if wxUSE_TIMEPICKCTRL
    detail_set_detail_impl(new detail_impl(parent));
#endif

    return *this;
}

std::time_t time_picker::get_time_t() const
{
#if wxUSE_TIMEPICKCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, static_cast<std::time_t>(-1));

    const wxDateTime datetime = impl->GetValue();
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::time_picker::get_time_t(): invalid std::time_t time"));

    return ((datetime.GetHour() * 60) + datetime.GetMinute()) * 60 + datetime.GetSecond();
#else
    return static_cast<std::time_t>(-1);
#endif
}

time_picker& time_picker::set_time_t(std::time_t t)
{
#if wxUSE_TIMEPICKCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    //BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::time_picker::set_time_t(): invalid std::time_t time"));

    std::time_t value = t;
    const int seconds = value % 60;
    value -= seconds;
    value /= 60;

    const int minutes = value % 60;
    value -= minutes;
    value /= 60;

    const int hours = value % 24;

    set_time(hours, minutes, seconds);
#endif

    return *this;
}

std::tm time_picker::get_tm() const
{
#if wxUSE_TIMEPICKCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, std::tm());

    const wxDateTime datetime = impl->GetValue();
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::time_picker::get_tm(): invalid datetime value"));

    const wxDateTime::Tm t = datetime.GetTm();

    struct std::tm result;
    result.tm_year  = 0;
    result.tm_mon   = 0;
    result.tm_mday  = 0;
    result.tm_hour  = t.hour;
    result.tm_min   = t.min;
    result.tm_sec   = t.sec;
    result.tm_yday  = 0;
    result.tm_isdst = -1;
    result.tm_wday  = 0;

    return result;
#else
    return std::tm();
#endif
}

time_picker& time_picker::set_tm(const std::tm& t)
{
#if wxUSE_TIMEPICKCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    if (   t.tm_hour < 0 || t.tm_hour > 23
        || t.tm_min  < 0 || t.tm_min  > 59
        || t.tm_sec  < 0 || t.tm_sec  > 61
       )
    {
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::time_picker::set_tm(): invalid std::tm time values"));
    }

    const wxDateTime datetime(t.tm_hour, t.tm_min, t.tm_sec);
    if ( !datetime.IsValid() )
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::time_picker::set_tm(): invalid std::tm time"));

    impl->SetValue(datetime);
#endif

    return *this;
}

void time_picker::get_time_raw(int* hours_ptr, int* minutes_ptr, int* seconds_ptr) const
{
#if wxUSE_TIMEPICKCTRL
    const detail_impl* impl = get_impl();
    wxCHECK(impl, );

    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    if ( impl->GetTime(&hours, &minutes, &seconds) )
    {
        if ( hours_ptr )
            *hours_ptr = hours;
        if ( minutes_ptr )
            *minutes_ptr = minutes;
        if ( seconds_ptr )
            *seconds_ptr = seconds;
    }
#endif
}

time_picker& time_picker::set_time(int hours, int minutes, int seconds)
{
#if wxUSE_TIMEPICKCTRL
    detail_impl* impl = get_impl();
    wxCHECK(impl, *this);

    if (   hours   < 0 || hours   > 23
        || minutes < 0 || minutes > 59
        || seconds < 0 || seconds > 61
       )
    {
        BOOST_THROW_EXCEPTION(std::out_of_range("boost::ui::time_picker::set_time(): invalid time values"));
    }

    impl->SetTime(hours, minutes, seconds);
#endif

    return *this;
}


void time_picker::on_change_raw(const boost::function<void()>& handler)
{
#if wxUSE_TIMEPICKCTRL
    native::bind_helper(*this, wxEVT_TIME_CHANGED, handler);
#endif
}

} // namespace ui
} // namespace boost
