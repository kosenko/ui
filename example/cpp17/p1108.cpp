// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Re-implemented example from P1108R0 C++ Standard proposal web_view
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1108r0.html

#include <boost/ui.hpp>

#include <chrono>

namespace ui = boost::ui;
using namespace std::chrono_literals; // c++14

int ui_main(int argc, char* argv[])
{
    const std::vector<std::string> args(argv, argv + argc);

    ui::on_timeout(2000ms, []
    {
    });

    std::ostringstream os;
    const char uri[] = "https://www.boost.org/";

    os << "<html><head><title>" << uri << "</title></head><body><p>" << uri << "</p><table>";
    for ( auto &a : args )
      os << "<tr><td>" << a << "</td></tr>" << "\n"; // we need some kind of "to_html" utility function.
    os << "</table>";
    os << "<p><a href=\"" << uri << "/more.html" << "\">more</a></p>";
    os << "<ul id='dl'></ul>";
    os << "</body></html>";

    ui::dialog dlg("web_view test app");
    ui::web_widget(dlg)
        .html(os.str());
    dlg.show_modal();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
