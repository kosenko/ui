// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_STRING_HPP
#define BOOST_UI_NATIVE_STRING_HPP

#include <boost/ui/native/config.hpp>

#include <vector>

class wxString;
class wxArrayString;

namespace boost  {
namespace ui     {
namespace native {

wxString from_uistring(const uistring& str);
uistring to_uistring(const wxString& str);
wxArrayString from_vector_uistring(const std::vector<uistring>& arr);

} // namespace native
} // namespace ui
} // namespace boost

#endif // BOOST_UI_STRING_HPP
