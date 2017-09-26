// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/painter.hpp>
#include <boost/ui/native/impl/canvas.hpp>
#include <boost/ui/native/color.hpp>
#include <boost/ui/native/image.hpp>
#include <boost/ui/native/font.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/native/widget.hpp>

#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/log.h>

namespace boost  {
namespace ui     {

nullopt_t nullopt(0);

namespace detail {

painter_impl::painter_impl(widget& parent)
#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    : m_gc(NULL)
#endif
{
    m_state.m_fill = m_state.m_stroke = colors::black();
    m_state.m_line_width = 1;
    m_state.m_cap = wxCAP_BUTT;
    m_state.m_join = wxJOIN_MITER;

    // 10px sans-serif
    m_state.m_font = wxFont(wxSize(10, 10), wxFONTFAMILY_SWISS,
                            wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    //m_state.m_font.SetFaceName(wxS("sans-serif"));

    begin_path();

    wxPanel* w = new wxPanel(native::from_widget(parent), wxID_ANY);
    set_native_handle(w);

    init_dc();

    w->Bind(wxEVT_PAINT, &painter_impl::on_paint, this);
}

painter_impl::~painter_impl()
{
#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    delete m_gc;
#endif
}

void painter_impl::init_dc()
{
    wxCHECK(m_native, );

    wxASSERT(!m_bitmap.IsOk());
    const wxSize size = m_native->GetSize();
    m_bitmap = wxBitmap(size);

    m_memdc.SelectObject(m_bitmap);
    m_memdc.SetBackground(m_native->GetBackgroundColour());
    m_memdc.Clear();

#ifndef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_start_point = wxPoint();
#endif
}

void painter_impl::prepare_dc()
{
    m_memdc.SelectObject(m_bitmap);

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    if ( !m_gc )
    {

        //m_gc = wxGraphicsRenderer::GetCairoRenderer()->CreateContextFromImage(m_memdc);
        m_gc = wxGraphicsContext::Create(m_memdc);
        wxASSERT(m_gc);

        if ( m_gc )
        {
#if 0
            const wxGraphicsRenderer* renderer = m_gc->GetRenderer();
            int major = -1, minor = -1, micro = -1;
            renderer->GetVersion(&major, &minor, &micro);
            wxLogDebug(wxS("wxGraphicsRenderer %s %d.%d.%d"),
                    renderer->GetName(), major, minor, micro);
#endif

            // Make it compatible with HTML Canvas
            m_gc->Translate(-0.5, -0.5);

            update_fill_font();
            update_pen();
            update_brush();
            begin_path();
        }
    }
#endif
}

void painter_impl::flush()
{
#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    if ( m_gc )
        m_gc->Flush();

    delete m_gc; // Flush graphics
    m_gc = NULL;
#endif

    m_memdc.SelectObject(wxNullBitmap);
}

void painter_impl::prepare()
{
    wxCHECK(m_native, );

    if ( m_native->GetSize() != m_bitmap.GetSize() )
    {
        flush();
        m_bitmap = wxBitmap();

        init_dc();

        wxASSERT(m_native->GetSize() == m_bitmap.GetSize());
    }

    prepare_dc();

    m_native->Refresh();
}

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT

wxGraphicsContext* painter_impl::get_context()
{
    prepare();

    wxASSERT(m_gc);
    return m_gc;
}

#endif

void painter_impl::on_paint(wxPaintEvent& e)
{
    e.Skip();

    flush();

    wxCHECK(m_native, );
    wxPaintDC dc(m_native);

    dc.DrawBitmap(m_bitmap, 0, 0);
}

void painter_impl::begin_path()
{
#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_path = wxGraphicsRenderer::GetDefaultRenderer()->CreatePath();
#else
    m_path.clear();
#endif
}

void painter_impl::save()
{
#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = get_context();
    wxCHECK(gc, );

    gc->PushState();
#endif

    m_states.push(m_state);
}

void painter_impl::restore()
{
#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = get_context();
    wxCHECK(gc, );

    gc->PopState();
#endif

    if ( m_states.empty() )
        return;
    m_state = m_states.top();
    m_states.pop();
    update_pen();
    update_brush();
}

void painter_impl::update_fill_font()
{
    wxASSERT(m_state.m_font.IsOk());

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = get_context();
    wxCHECK(gc, );

    gc->SetFont(m_state.m_font, native::from_color(m_state.m_fill));
#else
    wxMemoryDC& memdc = GetMemoryDCRef();
    memdc.SetFont(m_state.m_font);
#endif
}

void painter_impl::update_brush()
{
    const wxBrush brush(native::from_color(m_state.m_fill));

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = get_context();
    wxCHECK(gc, );

    gc->SetBrush(brush);
#else
    wxMemoryDC& memdc = GetMemoryDCRef();
    memdc.SetBrush(brush);
#endif
}

void painter_impl::update_pen()
{
    wxPen pen(native::from_color(m_state.m_stroke), m_state.m_line_width);
    pen.SetCap(m_state.m_cap);
    pen.SetJoin(m_state.m_join);
    if ( !m_state.m_dashes.empty() )
    {
        pen.SetStyle(wxPENSTYLE_USER_DASH);
        pen.SetDashes(m_state.m_dashes.size(), &m_state.m_dashes[0]);
    }

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = get_context();
    wxCHECK(gc, );

    gc->SetPen(pen);
#else
    wxMemoryDC& memdc = GetMemoryDCRef();
    memdc.SetPen(pen);
#endif
}

} // namespace detail

//-----------------------------------------------------------------------------

painter::painter(detail::painter_impl* impl) : m_impl(impl)
{
    wxCHECK(m_impl, );

    // Initialize and don't reset path later
    m_impl->prepare();
}

void painter::save_raw()
{
    wxCHECK(m_impl, );

    m_impl->save();
}

void painter::restore_raw()
{
    wxCHECK(m_impl, );

    m_impl->restore();
}

void painter::scale_raw(gcoord_type x, gcoord_type y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->Scale(x, y);
#endif
}

void painter::rotate_raw(gcoord_type angle)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->Rotate(angle);
#endif
}

void painter::translate_raw(gcoord_type x, gcoord_type y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->Translate(x, y);
#endif
}

void painter::fill_color_raw(const color& c)
{
    wxCHECK(m_impl, );

    m_impl->m_state.m_fill = c;
    m_impl->update_brush();
}

void painter::stroke_color_raw(const color& c)
{
    wxCHECK(m_impl, );

    m_impl->m_state.m_stroke = c;
    m_impl->update_pen();
}

void painter::clear_rect_raw(gcoord_type x, gcoord_type y,
                             gcoord_type width, gcoord_type height)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    // TODO: Use transparent brush
    //gc->SetBrush(wxTransparentColor);
    gc->SetBrush(m_impl->GetMemoryDCRef().GetBackground());
    gc->SetPen(*wxTRANSPARENT_PEN);
    const wxCompositionMode oldMode = gc->GetCompositionMode();
    gc->SetCompositionMode(wxCOMPOSITION_SOURCE);

    gc->DrawRectangle(x, y, width, height);

    gc->SetCompositionMode(oldMode);
#else
    wxMemoryDC& memdc = m_impl->GetMemoryDCRef();
    memdc.SetPen(*wxTRANSPARENT_PEN);
    //memdc.SetBrush(m_impl->GetBackgroundColour());
    memdc.DrawRectangle(x, y, width, height);
#endif

    m_impl->update_pen();
    m_impl->update_brush();
}

void painter::fill_rect_raw(gcoord_type x, gcoord_type y,
                            gcoord_type width, gcoord_type height)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->SetPen(*wxTRANSPARENT_PEN);
    gc->DrawRectangle(x, y, width, height);
#else
    wxMemoryDC& memdc = m_impl->GetMemoryDCRef();
    memdc.SetPen(*wxTRANSPARENT_PEN);
    memdc.DrawRectangle(x, y, width, height);
#endif

    m_impl->update_pen();
}

void painter::stroke_rect_raw(gcoord_type x, gcoord_type y,
                              gcoord_type width, gcoord_type height)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawRectangle(x, y, width, height);
#else
    wxMemoryDC& memdc = m_impl->GetMemoryDCRef();
    memdc.SetBrush(*wxTRANSPARENT_BRUSH);
    memdc.DrawRectangle(x, y, width, height);
#endif

    m_impl->update_brush();
}

void painter::fill_text_raw(const uistring& text, gcoord_type x, gcoord_type y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    const wxString str = native::from_uistring(text);
    m_impl->update_fill_font();
    wxDouble height = 0;
    gc->GetTextExtent(str, NULL, &height);
    gc->DrawText(str, x, y - height);
#else
    wxMemoryDC& memdc = m_impl->GetMemoryDCRef();
    const wxString str = native::from_uistring(text);
    m_impl->update_fill_font();
    wxCoord height = 0;
    memdc.GetTextExtent(str, NULL, &height);
    memdc.DrawText(str, x, y - height);
#endif
}

void painter::draw_image_raw(const image& img, gcoord_type dx, gcoord_type dy)
{
    wxCHECK(m_impl, );

    const wxBitmap* bitmap = native::from_image_ptr(img);
    wxCHECK(bitmap, );
    wxCHECK(bitmap->IsOk(), );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->DrawBitmap(*bitmap, dx, dy, bitmap->GetWidth(), bitmap->GetHeight());
#else
    wxMemoryDC& memdc = m_impl->GetMemoryDCRef();
    memdc.DrawBitmap(*bitmap, dx, dy);
#endif
}

void painter::begin_path_raw()
{
    wxCHECK(m_impl, );

    m_impl->begin_path();
}

void painter::fill_raw()
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->FillPath(m_impl->m_path);
#endif
}

void painter::stroke_raw()
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxGraphicsContext* gc = m_impl->get_context();
    wxCHECK(gc, );

    gc->StrokePath(m_impl->m_path);
#else
    if ( !m_impl->m_path.empty() )
    {
        typedef detail::painter_impl::path_type::const_iterator const_iterator;
        const_iterator start = m_impl->m_path.begin();
        const_iterator iter = start;
        ++iter;
        wxMemoryDC& memdc = m_impl->GetMemoryDCRef();
        for ( ; iter != m_impl->m_path.end(); ++iter )
        {
            memdc.DrawLine(*start, *iter);
            start = iter;
        }
    }
#endif
}

void painter::line_width_raw(gcoord_type width)
{
    wxCHECK(m_impl, );

    m_impl->m_state.m_line_width = width;
    m_impl->update_pen();
}

void painter::line_cap_raw(ui::line_cap lc)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxPenCap cap = wxCAP_INVALID;
    switch ( boost::native_value(lc) )
    {
        case ui::line_cap::butt:   cap = wxCAP_BUTT;       break;
        case ui::line_cap::round:  cap = wxCAP_ROUND;      break;
        case ui::line_cap::square: cap = wxCAP_PROJECTING; break;
    }
    wxCHECK(cap != wxCAP_INVALID, );
    m_impl->m_state.m_cap = cap;
    m_impl->update_pen();
#endif
}

void painter::line_join_raw(ui::line_join lj)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    wxPenJoin join = wxJOIN_INVALID;
    switch ( boost::native_value(lj) )
    {
        case ui::line_join::round: join = wxJOIN_ROUND; break;
        case ui::line_join::bevel: join = wxJOIN_BEVEL; break;
        case ui::line_join::miter: join = wxJOIN_MITER; break;
    }
    wxCHECK(join != wxJOIN_INVALID, );
    m_impl->m_state.m_join = join;
    m_impl->update_pen();
#endif
}

void painter::line_dash_raw(const std::vector<gcoord_type>& segments)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    const gcoord_type line_width = m_impl->m_state.m_line_width;
    const double dashUnit = line_width < 1.0 ? 1.0 : line_width;
    m_impl->m_state.m_dashes.clear();
    m_impl->m_state.m_dashes.reserve(segments.size());
    for ( std::vector<gcoord_type>::const_iterator iter = segments.begin();
         iter != segments.end(); ++iter )
    {
        m_impl->m_state.m_dashes.push_back(*iter / dashUnit);
    }
    m_impl->update_pen();
#endif
}

void painter::reset_line_dash_raw()
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_state.m_dashes.clear();
    m_impl->update_pen();
#endif
}

void painter::font_raw(const ui::font& f)
{
    wxCHECK(f.valid(), );
    wxCHECK(m_impl, );

    m_impl->m_state.m_font = native::from_font(f);
    m_impl->update_fill_font();
}

ui::font painter::font() const
{
    wxCHECK(m_impl, ui::font());

    return native::to_font(m_impl->m_state.m_font);
}

void painter::close_path_raw()
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.CloseSubpath();
#else
    m_impl->m_path.push_back(m_impl->m_start_point);
#endif
}

void painter::move_to_raw(gcoord_type x, gcoord_type y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.MoveToPoint(x, y);
#else
    m_impl->m_start_point = wxPoint(x, y);
#endif
}

void painter::line_to_raw(gcoord_type x, gcoord_type y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.AddLineToPoint(x, y);
#else
    if ( m_impl->m_path.empty() )
        m_impl->m_path.push_back(m_impl->m_start_point);
    m_impl->m_path.push_back(wxPoint(x, y));
#endif
}

void painter::quadratic_curve_to_raw(gcoord_type cpx, gcoord_type cpy,
                                     gcoord_type   x, gcoord_type   y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.AddQuadCurveToPoint(cpx, cpy, x, y);
#endif
}

void painter::bezier_curve_to_raw(gcoord_type cp1x, gcoord_type cp1y,
                                  gcoord_type cp2x, gcoord_type cp2y,
                                  gcoord_type    x, gcoord_type    y)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.AddCurveToPoint(cp1x, cp1y, cp2x, cp2y, x, y);
#endif
}

void painter::arc_raw(gcoord_type x, gcoord_type y, gcoord_type radius,
                      gcoord_type start_angle, gcoord_type end_angle, bool anticlockwise)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.AddArc(x, y, radius, start_angle, end_angle, !anticlockwise);
#endif
}

void painter::rect_raw(gcoord_type x, gcoord_type y, gcoord_type w, gcoord_type h)
{
    wxCHECK(m_impl, );

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    m_impl->m_path.AddRectangle(x, y, w, h);
#endif
}

painter::native_handle_type painter::native_handle()
{
    wxCHECK(m_impl, NULL);

#ifdef BOOST_UI_USE_GRAPHICS_CONTEXT
    return m_impl->get_context();
#else
    return &m_impl->GetMemoryDCRef();
#endif
}

} // namespace ui
} // namespace boost
