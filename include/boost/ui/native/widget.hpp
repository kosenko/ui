// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_WIDGET_HPP
#define BOOST_UI_NATIVE_WIDGET_HPP

class wxWindow;

#include <boost/ui/widget.hpp>
#include <boost/ui/detail/widget.hpp> // TODO: Remove

namespace boost  {
namespace ui     {
namespace native {

inline wxWindow* from_widget(ui::widget& w)
{
    return static_cast<wxWindow*>(w.native_handle());
}

inline const wxWindow* from_widget(const ui::widget& w)
{
    return static_cast<const wxWindow*>(w.native_handle());
}

template <class T>
T* impl(ui::widget& w)
{
    return dynamic_cast<T*>(from_widget(w));
}

template <class T>
const T* impl(const ui::widget& w)
{
    return dynamic_cast<const T*>(from_widget(w));
}

template <class T1, class T2>
T1* impl(ui::widget& w)
{
    return static_cast<T1*>(dynamic_cast<T2*>(from_widget(w)));
}

template <class T1, class T2>
const T1* impl(const ui::widget& w)
{
    return static_cast<const T1*>(dynamic_cast<const T2*>(from_widget(w)));
}

} // namespace native
} // namespace ui
} // namespace boost

#endif // BOOST_UI_NATIVE_WIDGET_HPP
