// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include <boost/ui/log.hpp>
#include <boost/ui/string_io.hpp>

#include <boost/core/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>

namespace ui = boost::ui;

void test_output(ui::log_string& l)
{
    l   << 12 << .34 << std::size_t(9) << true
        << "char*" << "wchar_t*" << 'C' << L'W'
        << "" << L"" << ui::uistring()
        << std::string("string") << std::wstring(L"wstring")
        << ui::uistring("uistring")
        ;
}

int cpp_main(int, char*[])
{
    {
        ui::uistring str;
        test_output(ui::log_string(str).nospaces().noquotes());
        BOOST_TEST_EQ(str, "120.349truechar*wchar_t*CWstringwstringuistring");
    }
    {
        ui::uistring str;
        test_output(ui::log_string(str).noquotes());
        BOOST_TEST_EQ(str, "12 0.34 9 true char* wchar_t* C W string wstring uistring");
    }
    {
        ui::uistring str;
        ui::log_string l(str);
        test_output(l);
        BOOST_TEST_EQ(str, "12 0.34 9 true \"char*\" \"wchar_t*\" 'C' 'W' \"\" \"\" \"\" \"string\" \"wstring\" \"uistring\"");
    }

    return boost::report_errors();
}
