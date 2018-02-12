// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/widget.hpp>
#include <boost/ui/native/event.hpp>
#include <boost/ui/native/font.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>

#include <wx/window.h>

namespace boost {
namespace ui    {

namespace detail {

void widget_detail_base::move(coord_type x, coord_type y)
{
    wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        impl->Move(x, y);
    else
    {
        m_x = x;
        m_y = y;
    }
}

void widget_detail_base::resize(coord_type width, coord_type height)
{
    wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        impl->SetSize(width, height);
    else
    {
        m_width  = width;
        m_height = height;
    }
}

coord_type widget_detail_base::x() const
{
    const wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        return impl->GetPosition().x;
    else
        return m_x;
}

coord_type widget_detail_base::y() const
{
    const wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        return impl->GetPosition().y;
    else
        return m_y;
}

coord_type widget_detail_base::width() const
{
    const wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        return impl->GetSize().x;
    else
        return m_width;
}

coord_type widget_detail_base::height() const
{
    const wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        return impl->GetSize().y;
    else
        return m_height;
}

void widget_detail_base::enable(bool do_enable)
{
    wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        impl->Enable(do_enable);
    else
        m_enabled = do_enable;
}

bool widget_detail_base::is_enabled() const
{
    const wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        return impl->IsEnabled();
    else
        return m_enabled;
}

void widget_detail_base::show(bool do_show)
{
    wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        impl->Show(do_show);
    else
    {
        m_shown = do_show;
        m_shown_modified = true;
    }
}

bool widget_detail_base::is_shown() const
{
    const wxWindow* impl = static_cast<wxWindow*>(native_handle());
    if ( impl )
        return impl->IsShownOnScreen();
    else
        return m_shown;
}

void widget_detail_base::create_base()
{
    if ( m_x != 0 && m_y != 0 )
        move(m_x, m_y);

    if ( m_width != 0 && m_height != 0 )
        resize(m_width, m_height);

    if ( !m_enabled )
        enable(m_enabled);

    if ( m_shown_modified )
        show(m_shown);
}

class detail_impl : public detail::widget_detail<wxWindow>
{
public:
    explicit detail_impl(native_handle_type handle)
    {
        wxASSERT(handle);
        set_native_handle(handle);
    }
};

} // namespace detail

widget::widget() : m_detail_impl(NULL) {}

widget::~widget()
{
    delete_last_detail_impl();
}

widget::widget(const widget& other)
{
    m_detail_impl = other.m_detail_impl;
    m_shared_count = other.m_shared_count;
}

widget& widget::operator=(const widget& other)
{
    if ( this != &other )
    {
        delete_last_detail_impl();

        m_detail_impl = other.m_detail_impl;
        m_shared_count = other.m_shared_count;
    }
    return *this;
}

void widget::delete_last_detail_impl()
{
    if ( m_shared_count.may_delete() )
    {
        delete m_detail_impl;
    }
}

void widget::detail_set_detail_impl(detail::widget_detail_base* d)
{
    wxASSERT(!m_detail_impl);
    delete m_detail_impl;

    m_detail_impl = d;
}

widget& widget::append(const widget& w)
{
    wxCHECK(!w.native_valid(), *this);

    w.m_detail_impl->create_native(*this);
    wxASSERT(w.native_valid());
    // TODO: Check if cache was destroyed here

    return *this;
}

widget& widget::move(coord_type x, coord_type y)
{
    wxCHECK(m_detail_impl, *this);
    m_detail_impl->move(x, y);
    return *this;
}

widget& widget::resize(coord_type width, coord_type height)
{
    wxCHECK(m_detail_impl, *this);
    m_detail_impl->resize(width, height);
    return *this;
}

coord_type widget::x() const
{
    wxCHECK(m_detail_impl, -1);
    return m_detail_impl->x();
}

coord_type widget::y() const
{
    wxCHECK(m_detail_impl, -1);
    return m_detail_impl->y();
}

coord_type widget::width() const
{
    wxCHECK(m_detail_impl, -1);
    return m_detail_impl->width();
}

coord_type widget::height() const
{
    wxCHECK(m_detail_impl, -1);
    return m_detail_impl->height();
}

widget& widget::enable(bool do_enable)
{
    wxCHECK(m_detail_impl, *this);
    m_detail_impl->enable(do_enable);
    return *this;
}

bool widget::is_enabled() const
{
    wxCHECK(m_detail_impl, false);
    return m_detail_impl->is_enabled();
}

widget& widget::show(bool do_show)
{
    wxCHECK(m_detail_impl, *this);
    m_detail_impl->show(do_show);
    return *this;
}

bool widget::is_shown() const
{
    wxCHECK(m_detail_impl, false);
    return m_detail_impl->is_shown();
}

widget& widget::tooltip(const uistring& text)
{
#if wxUSE_TOOLTIPS
    wxWindow* impl = native::from_widget(*this);
    wxCHECK(impl, *this);

    impl->SetToolTip(native::from_uistring(text));
#endif

    return *this;
}

uistring widget::tooltip() const
{
#if wxUSE_TOOLTIPS
    const wxWindow* impl = native::from_widget(*this);
    wxCHECK(impl, uistring());

    return native::to_uistring(impl->GetToolTipText());
#else
    return uistring();
#endif
}

widget& widget::font(const ui::font& f)
{
    wxCHECK(f.valid(), *this);

    wxWindow* impl = native::from_widget(*this);
    wxCHECK(impl, *this);

    impl->SetFont(native::from_font(f));

    return *this;
}

ui::font widget::font() const
{
    const wxWindow* impl = native::from_widget(*this);
    wxCHECK(impl, ui::font());

    return native::to_font(impl->GetFont());
}

void widget::on_resize_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_SIZE, handler);
}

void widget::on_key_press_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_CHAR, handler);
}

void widget::on_key_press_event_raw(const boost::function<void(key_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_CHAR, handler);
}

void widget::on_key_down_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_KEY_DOWN, handler);
}

void widget::on_key_down_event_raw(const boost::function<void(key_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_KEY_DOWN, handler);
}

void widget::on_key_up_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_KEY_UP, handler);
}

void widget::on_key_up_event_raw(const boost::function<void(key_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_KEY_UP, handler);
}

void widget::on_left_mouse_down_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_LEFT_DOWN, handler);
}

void widget::on_left_mouse_down_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_LEFT_DOWN, handler);
}

void widget::on_left_mouse_up_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_LEFT_UP, handler);
}

void widget::on_left_mouse_up_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_LEFT_UP, handler);
}

void widget::on_right_mouse_down_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_RIGHT_DOWN, handler);
}

void widget::on_right_mouse_down_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_RIGHT_DOWN, handler);
}

void widget::on_right_mouse_up_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_RIGHT_UP, handler);
}

void widget::on_right_mouse_up_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_RIGHT_UP, handler);
}

void widget::on_middle_mouse_down_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_MIDDLE_DOWN, handler);
}

void widget::on_middle_mouse_down_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_MIDDLE_DOWN, handler);
}

void widget::on_middle_mouse_up_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_MIDDLE_UP, handler);
}

void widget::on_middle_mouse_up_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_MIDDLE_UP, handler);
}

void widget::on_left_mouse_double_click_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_LEFT_DCLICK, handler);
}

void widget::on_left_mouse_double_click_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_LEFT_DCLICK, handler);
}

void widget::on_right_mouse_double_click_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_RIGHT_DCLICK, handler);
}

void widget::on_right_mouse_double_click_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_RIGHT_DCLICK, handler);
}

void widget::on_middle_mouse_double_click_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_MIDDLE_DCLICK, handler);
}

void widget::on_middle_mouse_double_click_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_MIDDLE_DCLICK, handler);
}

void widget::on_mouse_move_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_MOTION, handler);
}

void widget::on_mouse_move_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_MOTION, handler);
}

namespace {

class mouse_drag_filter
{
public:
    bool operator()(wxMouseEvent& wxevent)
    {
        return wxevent.ButtonIsDown(wxMOUSE_BTN_ANY);
    }
};

} // namespace unnamed

void widget::on_mouse_drag_raw(const boost::function<void()>& handler)
{
    const boost::function<bool(wxMouseEvent&)> filter = mouse_drag_filter();
    native::bind_helper(*this, wxEVT_MOTION, handler, filter);
}

void widget::on_mouse_drag_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    const boost::function<bool(wxMouseEvent&)> filter = mouse_drag_filter();
    native::bind_event_helper(*this, wxEVT_MOTION, handler, filter);
}

void widget::on_mouse_enter_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_ENTER_WINDOW, handler);
}

void widget::on_mouse_enter_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_ENTER_WINDOW, handler);
}

void widget::on_mouse_leave_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_LEAVE_WINDOW, handler);
}

void widget::on_mouse_leave_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_LEAVE_WINDOW, handler);
}

void widget::on_context_menu_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_CONTEXT_MENU, handler);
}

void widget::on_context_menu_event_raw(const boost::function<void(mouse_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_CONTEXT_MENU, handler);
}

void widget::on_mouse_wheel_raw(const boost::function<void()>& handler)
{
    native::bind_helper(*this, wxEVT_MOUSEWHEEL, handler);
}

void widget::on_mouse_wheel_event_raw(const boost::function<void(wheel_event&)>& handler)
{
    native::bind_event_helper(*this, wxEVT_MOUSEWHEEL, handler);
}

widget::native_handle_type widget::native_handle()
{
    return m_detail_impl ? m_detail_impl->native_handle() : NULL;
}

const widget::native_handle_type widget::native_handle() const
{
    return m_detail_impl ? m_detail_impl->native_handle() : NULL;
}

native_widget::native_widget(native_handle_type handle)
{
    // TODO: Don't create new object again for same handle
    detail_set_detail_impl(new detail::detail_impl(handle));
}

} // namespace ui
} // namespace boost
