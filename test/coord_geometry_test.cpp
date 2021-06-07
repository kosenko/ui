// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#if defined(__cplusplus) && __cplusplus >= 201703L

#define BOOST_UI_USE_GEOMETRY

#include "coord_test.cpp"

#else

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

int cpp_main(int argc, char* argv[])
{
    return boost::report_errors();
}

#endif
