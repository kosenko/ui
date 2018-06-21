// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file strings_box.hpp Widget with array of strings

#ifndef BOOST_UI_STRINGS_BOX_HPP
#define BOOST_UI_STRINGS_BOX_HPP

#include <boost/ui/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/ui/widget.hpp>

#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <algorithm> // for std::copy()
#include <iterator> // std::back_inserter()

namespace boost {
namespace ui    {

#ifndef DOXYGEN

namespace detail {

template <class Iterator>
std::vector<uistring> begin_end_to_vector_uistring(Iterator first, Iterator last)
{
    std::vector<uistring> result;
    result.reserve(last - first);
    std::copy(first, last, std::back_inserter(result));
    return result;
}

template <class Range>
std::vector<uistring> range_to_vector_uistring(const Range& r)
{
    std::vector<uistring> result;
    result.reserve(boost::size(r));
    std::copy(boost::begin(r), boost::end(r), std::back_inserter(result));
    return result;
}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
template <class T>
std::vector<uistring>
initializer_list_to_vector_uistring(std::initializer_list<T> list)
{
    std::vector<uistring> result;
    result.reserve(list.size());
    std::copy(list.begin(), list.end(), std::back_inserter(result));
    return result;
}
#endif

} // namespace detail

#endif

/// @brief Abstract widget that holds array of strings
/// @ingroup strings

class BOOST_UI_DECL strings_box : public widget
{
public:
    /// String type
    typedef uistring value_type;

    /// Integral type
    typedef index_type size_type;

    /// Invalid index
    static const size_type npos = nindex;

    /// @brief Returns specified element with bounds checking
    /// @throw std::out_of_range If @a pos is an invalid index
    uistring at(size_type pos) const;

    /// Retuns specified element
    uistring operator[](size_type pos) const;

    /// Checks whether the container has options
    bool empty() const { return size() == 0; }

    /// Returns the number of options
    size_type size() const;

    /// Clears the contents
    void clear();

    ///@{ Replaces the contents of the container
    strings_box& assign(const std::vector<uistring>& options)
        { clear(); return append(options); }

    strings_box& assign(size_type count, const value_type& value)
        { return assign(std::vector<uistring>(count, value)); }

    template <class Iterator>
    strings_box& assign(Iterator first, Iterator last)
        { return assign(detail::begin_end_to_vector_uistring(first, last)); }

    template <class Range>
    strings_box& assign(const Range& r)
        { return assign(detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    strings_box& assign(std::initializer_list<T> list)
        { return assign(detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    ///@{ Appends contents to the end
    strings_box& append(const std::vector<uistring>& options);

    strings_box& append(size_type count, const value_type& value)
        { return append(std::vector<uistring>(count, value)); }

    template <class Iterator>
    strings_box& append(Iterator first, Iterator last)
        { return append(detail::begin_end_to_vector_uistring(first, last)); }

    template <class Range>
    strings_box& append(const Range& r)
        { return append(detail::range_to_vector_uistring(r)); }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T>
    strings_box& append(std::initializer_list<T> list)
        { return append(detail::initializer_list_to_vector_uistring(list)); }
#endif
    ///@}

    /// Appends the given string value to the end
    void push_back(const uistring& value);

    /// Selects specified element
    strings_box& select(size_type pos);

private:
    void check_range(size_type pos) const;

    class native_impl;
    native_impl* get_native();
    const native_impl* get_native() const;
};

} // namespace ui
} // namespace boost

#endif // BOOST_UI_STRINGS_BOX_HPP
