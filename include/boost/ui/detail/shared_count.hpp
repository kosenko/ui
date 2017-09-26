// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_DETAIL_SHARED_COUNT_HPP
#define BOOST_UI_DETAIL_SHARED_COUNT_HPP

namespace boost  {
namespace ui     {
namespace detail {

class BOOST_UI_DECL shared_count
{
public:
    shared_count() { m_use_count = new long(1); }
    explicit shared_count(const shared_count& other)
    {
        m_use_count = other.m_use_count;
        add_ref();
    }
    shared_count& operator=(const shared_count& other)
    {
        if ( this != &other )
        {
            dec_ref();

            m_use_count = other.m_use_count;
            add_ref();
        }
        return *this;
    }
    ~shared_count() { dec_ref(); }

    long use_count() const { return *m_use_count; }

private:
    void add_ref()
    {
        ++*m_use_count;
    }
    void dec_ref()
    {
        if ( --*m_use_count == 0 )
            delete m_use_count;
    }

    long* m_use_count;
};

} // namespace detail
} // namespace ui
} // namespace boost

#endif // BOOST_UI_DETAIL_SHARED_COUNT_HPP
