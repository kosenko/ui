// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#define BOOST_UI_SOURCE

#include <boost/ui/stream.hpp>
#include <boost/ui/native/string.hpp>

#include <wx/string.h>

namespace boost {
namespace ui    {

uiostringstream& uiostringstream::operator<<(float value)
{
    m_buffer += native::to_uistring(wxString() << value);
    return *this;
}

uiostringstream& uiostringstream::operator<<(double value)
{
    m_buffer += native::to_uistring(wxString() << value);
    return *this;
}

} // namespace ui
} // namespace boost
