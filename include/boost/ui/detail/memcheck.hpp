// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_DETAIL_MEMCHECK_HPP
#define BOOST_UI_DETAIL_MEMCHECK_HPP

#ifndef NDEBUG
#define BOOST_UI_DEBUG_HOOKS
#endif

namespace boost  {
namespace ui     {
namespace detail {

class memcheck
{
public:
    memcheck() { inc(); }
    explicit memcheck(const memcheck& other) { inc(); }
    ~memcheck() { dec(); }

#ifdef BOOST_UI_DEBUG_HOOKS
    static int count() { return s_count; }
#endif

private:
#ifdef BOOST_UI_DEBUG_HOOKS
    void inc() { ++s_count; }
    void dec() { --s_count; }
    static int s_count;
#else
    void inc() {}
    void dec() {}
#endif
};

} // namespace detail
} // namespace ui
} // namespace boost

#endif // BOOST_UI_DETAIL_MEMCHECK_HPP
