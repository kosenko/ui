// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui/stream.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

namespace ui = boost::ui;

template <class Stream>
void test_stream_api()
{
    {
        Stream ss;
        BOOST_TEST(ss.str() == "");

        ss << 'A' << "aA" << std::string("1") << 3 << 1.2 << true << false << std::endl;
        BOOST_TEST(ss.str() == "AaA131.210\n");
    }
    {
        Stream ss("x1");
        BOOST_TEST(ss.str() == "x1");

        ss.str("y2");
        BOOST_TEST(ss.str() == "y2");
    }
}

template <class Stream>
void test_wstream_api()
{
    {
        Stream ss;
        ss << L'B' << L"bB" << std::wstring(L"2");
        BOOST_TEST(ss.str() == L"BbB2");
    }
}

int cpp_main(int, char*[])
{
    test_stream_api<std::ostringstream>();
    test_stream_api<ui::uiostringstream>();

    test_wstream_api<std::wostringstream>();
    test_wstream_api<ui::uiostringstream>();

    {
#ifndef BOOST_NO_CXX11_CHAR16_T
        ui::uiostringstream ss;
        ss << u'C' << u"cC" << std::u16string(u"3");
        BOOST_TEST(ss.str() == "CcC3");
#endif
    }
    {
#ifndef BOOST_NO_CXX11_CHAR32_T
        ui::uiostringstream ss;
        ss << U'D' << U"dD" << std::u32string(U"4");
        BOOST_TEST(ss.str() == "DdD4");
#endif
    }
    {
        ui::uiostringstream ss;

        void* ptr = reinterpret_cast<void*>(0x42);
        ss  << ptr;
        BOOST_TEST_NE(ss.str().wstring().find(L"42"), -1);
    }
    {
        ui::uiostringstream ss1("1");
        ui::uiostringstream ss2("2");
        BOOST_TEST(ss1.str() == "1");
        BOOST_TEST(ss2.str() == "2");

        ss1.swap(ss2);
        BOOST_TEST(ss1.str() == "2");
        BOOST_TEST(ss2.str() == "1");

        std::swap(ss1, ss2);
        BOOST_TEST(ss1.str() == "1");
        BOOST_TEST(ss2.str() == "2");
    }

    return boost::report_errors();
}
