// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui/string.hpp>
#include <boost/ui/string_io.hpp>

#include <boost/functional/hash.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

#include <sstream>

namespace ui = boost::ui;

template <class String>
void test_std_string_api_compatibility()
{
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    {
        String str1("test");
        String str2 = std::move(str1);
        BOOST_TEST_EQ(str2, "test");

        str1 = std::move(str2);
        BOOST_TEST_EQ(str1, "test");

        str2.assign(std::move(str1));
        BOOST_TEST_EQ(str2, "test");

        str1 = "test";
        str2 = "TEST";
        BOOST_TEST_EQ(std::move(str1) + std::move(str2), "testTEST");

        const String xstr("X");

        str1 = "test";
        BOOST_TEST_EQ(std::move(str1) + xstr, "testX");

        str1 = "test";
        BOOST_TEST_EQ(xstr + std::move(str1), "Xtest");

        str1 = "test";
        BOOST_TEST_EQ(std::move(str1) + "1", "test1");

        str1 = "test";
        BOOST_TEST_EQ(std::move(str1) + '1', "test1");
    }
#endif

    {
        String str("abc");
        str.append(std::string("de"));
        BOOST_TEST_EQ(str, "abcde");
        str.push_back('f');
        BOOST_TEST_EQ(str, "abcdef");
        str.push_back(L'g');
        BOOST_TEST_EQ(str, "abcdefg");
        str.append(2, 'C');
        BOOST_TEST_EQ(str, "abcdefgCC");

        str.assign("=");
        str = str + String("A");
        str = str + 'B';
        str = str + "C";
        str = String("A") + str;
        str = 'B' + str;
        str = "C" + str;
        BOOST_TEST_EQ(str, "CBA=ABC");
    }
}

template <class String>
void test_std_wstring_api_compatibility()
{
    {
        String str(L"xyz");
        BOOST_TEST(str == L"xyz");
        str.append(3, L'a');
        BOOST_TEST(str == L"xyzaaa");
    }
}

void test_api_compatibility()
{
    test_std_string_api_compatibility<std::string>();
    test_std_string_api_compatibility<ui::uistring>();

    test_std_wstring_api_compatibility<std::wstring>();
    test_std_wstring_api_compatibility<ui::uistring>();
}

template <class CharT>
void test_ostream()
{
    std::basic_ostringstream<CharT> oss_actual;
    oss_actual << ui::uistring("xy");

    std::basic_ostringstream<CharT> oss_expected;
    oss_expected << CharT('x') <<  CharT('y');
    BOOST_TEST(oss_actual.str() == oss_expected.str());

    //oss_actual << std::endl; // TODO: For char16_t and char32_t
}

template <class CharT>
void test_istream()
{
    const CharT chars[] = { CharT('y'), CharT('z'), 0 };
    std::basic_istringstream<CharT> iss(chars);
    ui::uistring str;
    iss >> str;
    BOOST_TEST(str == chars);
}

template <class CharT>
void test_getline()
{
    const CharT chars[] = { CharT('a'), CharT('b'), CharT(' '),
        CharT('c'), CharT('d'), CharT('\n'), CharT('x'), 0 };
    std::basic_istringstream<CharT> iss(chars);
    ui::uistring str;

    BOOST_TEST(std::getline(iss, str, CharT(' ')));
    const CharT chars2[] = { CharT('a'), CharT('b'), 0 };
    BOOST_TEST_EQ(str, chars2);

    BOOST_TEST(std::getline(iss, str));
    const CharT chars3[] = { CharT('c'), CharT('d'), 0 };
    BOOST_TEST_EQ(str, chars3);
}

int cpp_main(int, char*[])
{
    test_api_compatibility();

    BOOST_TEST(ui::uistring().empty());
    BOOST_TEST(ui::uistring("").empty());
    BOOST_TEST(!ui::uistring("test").empty());
    BOOST_TEST(!ui::uistring(std::string("test")).empty());
    BOOST_TEST(!ui::uistring(L"test").empty());
    BOOST_TEST(!ui::uistring(std::wstring(L"test")).empty());

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    BOOST_TEST_EQ(ui::uistring({ 'I', 'L' }), "IL");
    BOOST_TEST_EQ(ui::uistring({ L'l', L'i' }), "li");
#ifndef BOOST_NO_CXX11_CHAR16_T
    BOOST_TEST_EQ(ui::uistring({ u'I', u'l' }), "Il");
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    BOOST_TEST_EQ(ui::uistring({ U'i', U'L' }), "iL");
#endif

    // http://en.wikipedia.org/wiki/Yi_(Cyrillic)
    BOOST_TEST_EQ(ui::uistring({ wchar_t(0x0457) }).wstring()[0], 0x0457);
#endif

    {
        ui::uistring str("test");
        str.shrink_to_fit();

        BOOST_TEST(!str.empty());
        str.clear();
        BOOST_TEST(str.empty());
    }

    BOOST_TEST(ui::uistring() == ui::uistring());
    BOOST_TEST(ui::uistring("test") == ui::uistring("test"));
    BOOST_TEST(!(ui::uistring("test") == ui::uistring("tset")));
    BOOST_TEST(ui::uistring("test") != ui::uistring("tset"));

    BOOST_TEST_EQ(ui::uistring(), "");
    BOOST_TEST_EQ(ui::uistring("test"), "test");

    BOOST_TEST(ui::uistring("test").wstring() == L"test");

    {
        // http://uk.wikipedia.org/wiki/%D0%9A%D0%B8%D1%97%D0%B2
        static const char charsUTF8[] = "\xD0\x9A\xD0\xB8\xD1\x97\xD0\xB2";
        // http://en.wikipedia.org/wiki/Ka_(Cyrillic)
        // http://en.wikipedia.org/wiki/I_(Cyrillic)
        // http://en.wikipedia.org/wiki/Yi_(Cyrillic)
        // http://en.wikipedia.org/wiki/Ve_(Cyrillic)

        const ui::uistring str = ui::utf8(charsUTF8);
        BOOST_TEST_EQ(str.u8string(), charsUTF8);
        BOOST_TEST_EQ(str.utf<char>(), charsUTF8);

        std::wstring wstr = str.wstring();
        BOOST_TEST_EQ(wstr.size(), 4u);
        BOOST_TEST_EQ(wstr[0], 0x041A);
        BOOST_TEST_EQ(wstr[1], 0x0438);
        BOOST_TEST_EQ(wstr[2], 0x0457);
        BOOST_TEST_EQ(wstr[3], 0x0432);
        BOOST_TEST(str.basic_string<wchar_t>() == wstr);
    }
#ifndef BOOST_NO_CXX11_CHAR16_T
    {
        // U+20B4 - Hryvnia sign
        static const char16_t charsUTF16[] = u"\u041a\u0438\u0457\u0432\u20b4";
        const ui::uistring str = charsUTF16;
        std::wstring wstr = str.wstring();
        BOOST_TEST_EQ(wstr.size(), 5u);
        BOOST_TEST_EQ(wstr[0], 0x041A);
        BOOST_TEST_EQ(wstr[1], 0x0438);
        BOOST_TEST_EQ(wstr[2], 0x0457);
        BOOST_TEST_EQ(wstr[3], 0x0432);
        BOOST_TEST_EQ(wstr[4], 0x20b4);
        BOOST_TEST(str.u16string() == charsUTF16);
        BOOST_TEST(str.utf<char16_t>() == charsUTF16);
        BOOST_TEST(str.basic_string<char16_t>() == charsUTF16);
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    {
        // U+1D11E - Musical symbol G-clef
        static const char32_t charsUTF32[] = U"\U0000041a\U00000438\U00000457\U00000432\U0001D11E";
        const ui::uistring str = charsUTF32;
        std::wstring wstr = str.wstring();
        BOOST_TEST_EQ(wstr.size(), 5u);
        BOOST_TEST_EQ(wstr[0], 0x041A);
        BOOST_TEST_EQ(wstr[1], 0x0438);
        BOOST_TEST_EQ(wstr[2], 0x0457);
        BOOST_TEST_EQ(wstr[3], 0x0432);
        if ( sizeof(wchar_t) == 2 )
            ; // TODO: Fix when sizeof(wchar_t) < sizeof(char32_t)
        else
        {
        BOOST_TEST_EQ(wstr[4], 0x1d11e);
        BOOST_TEST(str.u32string() == charsUTF32);
        BOOST_TEST(str.utf<char32_t>() == charsUTF32);
        BOOST_TEST(str.basic_string<char32_t>() == charsUTF32);
        }
    }
#endif
    {
        ui::uistring a("a1"), b("b2");
        a.swap(b);
        BOOST_TEST_EQ(a, "b2");
        BOOST_TEST_EQ(b, "a1");
        std::swap(a, b);
        BOOST_TEST_EQ(a, "a1");
        BOOST_TEST_EQ(b, "b2");

        BOOST_TEST(a < b);
        BOOST_TEST(a <= b);
        BOOST_TEST(b > a);
        BOOST_TEST(b >= a);
        BOOST_TEST(a == a);
        BOOST_TEST(a != b);

        boost::hash<ui::uistring> boost_hash;
        BOOST_TEST_EQ(boost_hash(a), boost_hash(a));
        BOOST_TEST_NE(boost_hash(a), boost_hash(b));

#ifndef BOOST_UI_NO_STD_HASH
        std::hash<ui::uistring> std_hash;
        BOOST_TEST_EQ(std_hash(a), std_hash(a));
        BOOST_TEST_NE(std_hash(a), std_hash(b));
#endif
    }
    {
        std::ostringstream oss;
        oss << ui::uistring("ostream");
        BOOST_TEST_EQ(oss.str(), "ostream");

        std::istringstream iss("istream");
        ui::uistring str;
        iss >> str;
        BOOST_TEST_EQ(str, "istream");
    }
    {
        std::wostringstream oss;
        oss << ui::uistring("wostream");
        BOOST_TEST(oss.str() == L"wostream");

        std::wistringstream iss(L"wistream");
        ui::uistring wstr;
        iss >> wstr;
        BOOST_TEST(wstr.wstring() == L"wistream");
    }

    {
        std::istringstream iss("ab cd\nx");
        ui::uistring str;
        BOOST_TEST(std::getline(iss, str, ' '));
        BOOST_TEST_EQ(str, "ab");
        BOOST_TEST(std::getline(iss, str));
        BOOST_TEST_EQ(str, "cd");
    }

    {
        std::wistringstream iss(L"ab cd\nx");
        ui::uistring str;
        BOOST_TEST(std::getline(iss, str, L' '));
        BOOST_TEST(str.wstring() == L"ab");
        BOOST_TEST(std::getline(iss, str));
        BOOST_TEST(str.wstring() == L"cd");
    }

    test_ostream<char>();
    test_istream<char>();
    test_getline<char>();
    test_ostream<wchar_t>();
    test_istream<wchar_t>();
    test_getline<wchar_t>();
#ifndef BOOST_NO_CXX11_CHAR16_T
    test_ostream<char16_t>();
    //test_istream<char16_t>();
    test_getline<char16_t>();
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    test_ostream<char32_t>();
    //test_istream<char32_t>();
    test_getline<char32_t>();
#endif

    return boost::report_errors();
}
