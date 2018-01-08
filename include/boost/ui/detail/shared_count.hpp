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
    class data_type
    {
    public:
        data_type() : m_use_count(1), m_attached(true) {}
        bool may_delete() const { return m_attached && m_use_count == 1; }

        long m_use_count;
        bool m_attached;
    };

public:
    shared_count() { m_data = new data_type; }
    explicit shared_count(const shared_count& other)
    {
        m_data = other.m_data;
        add_ref();
    }
    shared_count& operator=(const shared_count& other)
    {
        if ( this != &other )
        {
            dec_ref();

            m_data = other.m_data;
            add_ref();
        }
        return *this;
    }
    ~shared_count() { dec_ref(); }

    long use_count() const { return m_data->m_use_count; }

    void detach() { m_data->m_attached = false; }
    bool may_delete() const { return m_data->may_delete(); }

private:
    void add_ref()
    {
        ++m_data->m_use_count;
    }
    void dec_ref()
    {
        if ( --m_data->m_use_count == 0 )
            delete m_data;
    }

    data_type* m_data;
};

} // namespace detail
} // namespace ui
} // namespace boost

#endif // BOOST_UI_DETAIL_SHARED_COUNT_HPP
