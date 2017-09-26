// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_DETAIL_WIDGET_HPP
#define BOOST_UI_DETAIL_WIDGET_HPP

#include <boost/ui/widget.hpp>

namespace boost  {
namespace ui     {
namespace detail {

class widget_detail_base
{
public:
    widget_detail_base() : m_x(0), m_y(0), m_width(0), m_height(0),
        m_enabled(true),
        m_shown(true), m_shown_modified(false) // TODO: Support wxTLWs
    {}
    virtual ~widget_detail_base() {}

    void create_native(widget& parent) { do_create_native(parent); }

    void move(coord_type x, coord_type y);
    void resize(coord_type width, coord_type height);
    coord_type x() const;
    coord_type y() const;
    coord_type width() const;
    coord_type height() const;
    void enable(bool do_enable);
    bool is_enabled() const;
    void show(bool do_show);
    bool is_shown() const;

    typedef void* native_handle_type;
    virtual native_handle_type native_handle() = 0;
    virtual const native_handle_type native_handle() const = 0;
    virtual void set_native_handle(native_handle_type n) = 0;

protected:
    void create_base();
    virtual void do_create_native(widget& parent) {} // = 0

private:
    // TODO: Move to cache
    coord_type m_x, m_y, m_width, m_height;
    bool m_enabled, m_shown, m_shown_modified;
};

class window_detail_base : public widget_detail_base
{
public:
    virtual void show_modal() = 0;
};

template <class TNative, class TBase>
class widget_detail_base_type : public TBase
{
public:
    widget_detail_base_type() : m_native(NULL) {}

    virtual       typename TBase::native_handle_type native_handle()       { return m_native; }
    virtual const typename TBase::native_handle_type native_handle() const { return m_native; }
    virtual void set_native_handle(typename TBase::native_handle_type n)
    {
        //assert(!m_native);
        //assert(n);

        m_native = static_cast<TNative*>(n);
    }

    void delete_native()
    {
        delete m_native;
        m_native = NULL;
    }

protected:
    TNative* m_native;
};

template <class TNative>
class widget_detail : public widget_detail_base_type<TNative, widget_detail_base>
{
};

template <class TNative>
class window_detail : public widget_detail_base_type<TNative, window_detail_base>
{
};

} // namespace detail
} // namespace ui
} // namespace boost

#endif // BOOST_UI_DETAIL_WIDGET_HPP
