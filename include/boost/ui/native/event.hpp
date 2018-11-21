// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_EVENT_HPP
#define BOOST_UI_NATIVE_EVENT_HPP

#include <boost/ui/native/config.hpp>
#include <boost/ui/native/widget.hpp>

#include <wx/window.h>

namespace boost  {
namespace ui     {
namespace native {

template <class NativeEvent>
class empty_filter
{
public:
    bool operator()(NativeEvent& wxevent) { return true; }
};

template <class NativeEvent>
class event_functor
{
public:
    event_functor(const boost::function<void()>& handler,
                  const boost::function<bool(NativeEvent&)>& filter)
        : m_handler(handler), m_filter(filter)
    {}

    void operator()(NativeEvent& wxevent)
    {
        wxevent.Skip();

        if ( !m_filter(wxevent) )
            return;

        m_handler();
    }

private:
    const boost::function<void()> m_handler;
    const boost::function<bool(NativeEvent&)> m_filter;
};


template <class EventTag>
void bind_helper(widget& w, EventTag eventType,
                 const boost::function<void()>& handler,
                 const boost::function<bool(typename EventTag::EventClass&)>& filter
                     = empty_filter<typename EventTag::EventClass>())
{
    wxWindow* impl = from_widget(w);
    wxCHECK_RET(impl, "Widget should be created");

    impl->Bind(eventType, event_functor<
        typename EventTag::EventClass>(handler, filter));
}

template <class NativeEvent, class UIEvent>
class event_functor_event
{
public:
    event_functor_event(const boost::function<void(UIEvent&)>& handler,
                        const boost::function<bool(NativeEvent&)>& filter)
        : m_handler(handler), m_filter(filter)
    {}

    void operator()(NativeEvent& wxevent)
    {
        wxevent.Skip();

        if ( !m_filter(wxevent) )
            return;

        UIEvent uievent;
        init(uievent, wxevent);
        m_handler(uievent);
    }

private:
    void init(UIEvent& uievent, NativeEvent& wxevent);

    const boost::function<void(UIEvent&)> m_handler;
    const boost::function<bool(NativeEvent&)> m_filter;
};

template <class EventTag, class UIEvent>
void bind_event_helper(widget& w, EventTag eventType,
                       const boost::function<void(UIEvent&)>& handler,
                       const boost::function<bool(typename EventTag::EventClass&)>& filter
                           = empty_filter<typename EventTag::EventClass>())
{
    wxWindow* impl = from_widget(w);
    wxCHECK_RET(impl, "Widget should be created");

    impl->Bind(eventType, event_functor_event<
        typename EventTag::EventClass, UIEvent>(handler, filter));
}

} // namespace native
} // namespace ui
} // namespace boost

#endif // BOOST_UI_NATIVE_EVENT_HPP
