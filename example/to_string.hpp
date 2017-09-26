// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_EXAMPLE_TO_STRING_HPP
#define BOOST_UI_EXAMPLE_TO_STRING_HPP

#include <string>
#include <sstream>

template <class T>
std::string to_string(T value)
{
    //return std::to_string(value);

    std::ostringstream ss;
    ss << value;
    return ss.str();
}

#endif // BOOST_UI_EXAMPLE_TO_STRING_HPP
