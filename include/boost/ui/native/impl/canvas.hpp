// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_IMPL_CANVAS_HPP
#define BOOST_UI_NATIVE_IMPL_CANVAS_HPP

#include <boost/ui/detail/widget.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <wx/panel.h>
#include <wx/image.h>

#include <wx/pen.h>

#include <stack>
#include <vector>

#if wxUSE_GRAPHICS_CONTEXT
#define BOOST_UI_USE_GRAPHICS_CONTEXT
#endif

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
#include <wx/graphics.h>
#endif

#include <wx/dcmemory.h>

namespace boost  {
namespace ui     {
namespace detail {

class painter_impl : public detail::widget_detail<wxPanel>
{
public:
    explicit painter_impl(widget& parent);
    virtual ~painter_impl();

    void prepare();
    void save();
    void restore();
    void update_brush();
    void begin_path();

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* get_context();
#endif
    wxMemoryDC& GetMemoryDCRef() { return m_memdc; }

    void update_pen();
    void update_fill_font();

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsPath m_path;
#else
    typedef std::vector<wxPoint> path_type;
    path_type m_path;
    wxPoint m_start_point;
#endif

    struct state
    {
        color m_fill;
        color m_stroke;
        int m_line_width;
        wxPenCap m_cap;
        wxPenJoin m_join;
        std::vector<wxDash> m_dashes;
        wxFont m_font;
    };

    state m_state;

private:
    void init_dc();
    void prepare_dc();
    void flush();

    void on_paint(wxPaintEvent& e);

    std::stack<state> m_states;

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* m_gc;
#endif
    wxBitmap m_bitmap;
    wxMemoryDC m_memdc;
};

} // namespace detail
} // namespace ui
} // namespace boost

#endif // BOOST_UI_NATIVE_IMPL_CANVAS_HPP
