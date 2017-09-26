// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file def.hpp Definitions

#ifndef BOOST_UI_DEF_HPP
#define BOOST_UI_DEF_HPP

#include <boost/ui/config.hpp>

namespace boost {
namespace ui    {

#ifndef DOXYGEN

struct nullopt_t {
    nullopt_t(int) {}
};

extern nullopt_t nullopt;

#endif

} // namespace ui
} // namespace boost

#endif // BOOST_UI_DEF_HPP
