// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/font.hpp>
#include <boost/ui/native/font.hpp>
#include <boost/ui/native/string.hpp>
#include <boost/ui/detail/memcheck.hpp>

#include <boost/throw_exception.hpp>

#include <wx/font.h>

#include <stdexcept>

namespace boost {
namespace ui    {

class font::impl : public wxFont, private detail::memcheck
{
public:
    impl() {}
    impl(const wxFont& font) : wxFont(font) {}
};

static wxFontFamily from_font_family(font::family f)
{
    wxFontFamily nf = wxFONTFAMILY_DEFAULT;
    switch ( boost::native_value(f) )
    {
        case font::family::serif:      nf = wxFONTFAMILY_ROMAN; break;
        case font::family::sans_serif: nf = wxFONTFAMILY_SWISS; break;
        case font::family::cursive:    nf = wxFONTFAMILY_SCRIPT; break;
        case font::family::fantasy:    nf = wxFONTFAMILY_DECORATIVE; break;
        case font::family::monospace:  nf = wxFONTFAMILY_TELETYPE; break;
        case font::family::other:
            BOOST_THROW_EXCEPTION(std::out_of_range("Invalid font family"));
    }
    return nf;
}

static font::family to_font_family(wxFontFamily nf)
{
    font::family f = font::family::other;
    switch ( nf )
    {
        case wxFONTFAMILY_ROMAN:      f = font::family::serif; break;
        case wxFONTFAMILY_SWISS:      f = font::family::sans_serif; break;
        case wxFONTFAMILY_SCRIPT:     f = font::family::cursive; break;
        case wxFONTFAMILY_DECORATIVE: f = font::family::fantasy; break;
        case wxFONTFAMILY_TELETYPE:   f = font::family::monospace; break;
        case wxFONTFAMILY_DEFAULT:
        case wxFONTFAMILY_UNKNOWN:
        case wxFONTFAMILY_MODERN:
            break;
    }
    return f;
}

static wxFontStyle from_font_slant(font::slant f)
{
    wxFontStyle ns = wxFONTSTYLE_NORMAL;
    switch ( boost::native_value(f) )
    {
        case font::slant::normal:  ns = wxFONTSTYLE_NORMAL; break;
        case font::slant::italic:  ns = wxFONTSTYLE_ITALIC; break;
        case font::slant::oblique: ns = wxFONTSTYLE_SLANT; break;
    }
    return ns;
}

static font::slant to_font_slant(wxFontStyle ns)
{
    font::slant s = font::slant::normal;
    switch ( ns )
    {
        case wxFONTSTYLE_NORMAL: s = font::slant::normal; break;
        case wxFONTSTYLE_ITALIC: s = font::slant::italic; break;
        case wxFONTSTYLE_SLANT:  s = font::slant::oblique; break;
        case wxFONTSTYLE_MAX: break;
    }
    return s;
}

static wxFontWeight from_font_weight(font::weight f)
{
    wxFontWeight nw = wxFONTWEIGHT_NORMAL;
    switch ( boost::native_value(f) )
    {
        case font::weight::normal: nw = wxFONTWEIGHT_NORMAL; break;
        case font::weight::bold:   nw = wxFONTWEIGHT_BOLD; break;
    }
    return nw;
}

static font::weight to_font_weight(wxFontWeight nw)
{
    font::weight s = font::weight::normal;
    switch ( nw )
    {
        case wxFONTWEIGHT_NORMAL: s = font::weight::normal; break;
        case wxFONTWEIGHT_LIGHT:
        case wxFONTWEIGHT_BOLD:   s = font::weight::bold; break;
        case wxFONTWEIGHT_MAX: break;
    }
    return s;
}

font::font() : m_impl(new impl)
{
}

font::font(const font& other) : m_impl(new impl)
{
    *m_impl = *other.m_impl;
}

font& font::operator=(const font& other)
{
    *m_impl = *other.m_impl;
    return *this;
}

font::~font()
{
    delete m_impl;
}

font::font(double pt, family f, slant s, weight w)
{
    if ( pt <= 0 )
        BOOST_THROW_EXCEPTION(std::out_of_range("Invalid font size"));

    const wxFontFamily nf = from_font_family(f);
    const wxFontStyle ns = from_font_slant(s);
    const wxFontWeight nw = from_font_weight(w);

    m_impl = new impl;
    m_impl->Create(pt, nf, ns, nw);
    wxASSERT(valid());
}

font::font(double pt, const uistring& n, slant s, weight w)
{
    if ( pt <= 0 )
        BOOST_THROW_EXCEPTION(std::out_of_range("Invalid font size"));

    const wxString faceName = native::from_uistring(n);
    const wxFontStyle ns = from_font_slant(s);
    const wxFontWeight nw = from_font_weight(w);

    m_impl = new impl;
    m_impl->Create(pt, wxFONTFAMILY_DEFAULT, ns, nw, false, faceName);
    if ( !valid() || !m_impl->SetFaceName(faceName) )
    {
        delete m_impl;
        BOOST_THROW_EXCEPTION(std::out_of_range("Invalid font name"));
    }
}

font& font::set_family(family f)
{
    m_impl->SetFamily(from_font_family(f));
    return *this;
}

font::family font::get_family() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("Invalid font"));

    return to_font_family(m_impl->GetFamily());
}

font& font::set_slant(slant s)
{
    m_impl->SetStyle(from_font_slant(s));
    return *this;
}

font::slant font::get_slant() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("Invalid font"));

    return to_font_slant(m_impl->GetStyle());
}

font& font::set_weight(weight w)
{
    m_impl->SetWeight(from_font_weight(w));
    return *this;
}

font::weight font::get_weight() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("Invalid font"));

    return to_font_weight(m_impl->GetWeight());
}

font& font::name(const uistring& n)
{
    if ( !m_impl->SetFaceName(native::from_uistring(n)) )
        BOOST_THROW_EXCEPTION(std::out_of_range("Invalid font name"));

    return *this;
}

uistring font::name() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("Invalid font"));

    return native::to_uistring(m_impl->GetFaceName());
}

font& font::size_pt(double pt)
{
    if ( pt <= 0 )
        BOOST_THROW_EXCEPTION(std::out_of_range("Invalid font size"));

    m_impl->SetPointSize(pt);

    return *this;
}

double font::size_pt() const
{
    if ( !valid() )
        BOOST_THROW_EXCEPTION(std::runtime_error("Invalid font"));

    return m_impl->GetPointSize();
}

bool font::valid() const BOOST_NOEXCEPT
{
    return m_impl->IsOk();
}

font font::caption() BOOST_NOEXCEPT
{
    return native::to_font(*wxNORMAL_FONT);
}

class native_helper
{
public:
    static ui::font to_font(const wxFont& f)
    {
        ui::font result;
        *result.m_impl = f;
        return result;
    }
};

namespace native {

wxFont from_font(ui::font& f)
{
    wxCHECK(f.valid(), wxFont());
    return *static_cast<wxFont*>(f.native_handle());
}

const wxFont from_font(const ui::font& f)
{
    wxCHECK(f.valid(), wxFont());
    return *static_cast<const wxFont*>(f.native_handle());
}

ui::font to_font(const wxFont& f)
{
    return native_helper::to_font(f);
}

} // namespace mative

} // namespace ui
} // namespace boost
