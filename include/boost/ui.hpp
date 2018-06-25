// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

/// @file ui.hpp Master Boost.UI file

#ifndef BOOST_UI_HPP
#define BOOST_UI_HPP

#include <boost/ui/application.hpp>
#include <boost/ui/audio.hpp>
#include <boost/ui/button.hpp>
#include <boost/ui/canvas.hpp>
#include <boost/ui/check_box.hpp>
#include <boost/ui/choice.hpp>
#include <boost/ui/color.hpp>
#include <boost/ui/color_io.hpp>
#include <boost/ui/combo_box.hpp>
#include <boost/ui/config.hpp>
#include <boost/ui/coord.hpp>
#include <boost/ui/coord_io.hpp>
#include <boost/ui/datetime.hpp>
#include <boost/ui/def.hpp>
#include <boost/ui/dialog.hpp>
#include <boost/ui/event.hpp>
#include <boost/ui/event_loop.hpp>
#include <boost/ui/font.hpp>
#include <boost/ui/frame.hpp>
#include <boost/ui/group_box.hpp>
#include <boost/ui/hyperlink.hpp>
#include <boost/ui/image.hpp>
#include <boost/ui/image_widget.hpp>
#include <boost/ui/label.hpp>
#include <boost/ui/layout.hpp>
#include <boost/ui/line.hpp>
#include <boost/ui/list_box.hpp>
#include <boost/ui/locale.hpp>
#include <boost/ui/log.hpp>
#include <boost/ui/menu.hpp>
#include <boost/ui/message.hpp>
#include <boost/ui/notebook.hpp>
#include <boost/ui/painter.hpp>
#include <boost/ui/panel.hpp>
#include <boost/ui/progress_bar.hpp>
#include <boost/ui/slider.hpp>
#include <boost/ui/status_bar.hpp>
#include <boost/ui/stream.hpp>
#include <boost/ui/string.hpp>
#include <boost/ui/string_io.hpp>
#include <boost/ui/strings_box.hpp>
#include <boost/ui/text_box.hpp>
#include <boost/ui/thread.hpp>
#include <boost/ui/web_widget.hpp>
#include <boost/ui/widget.hpp>
#include <boost/ui/window.hpp>

/** @mainpage

@tableofcontents

@section introduction Introduction

Boost.UI is a C++ User Interface (GUI) Boost library that
- is cross-platform
- uses native system-provided widgets
- has STL-like and Boost-like API
- compatible with other Boost libraries
- supports modern C++11/14/17 features

It supports @ref graphics, various @ref widget, @ref event, @ref layout.

@section motivation Motivation
C++ programs should have a better way to interact with humans then std::cin / std::cout.

@section examples_and_screenshots Examples and screenshots
@subsection hello "Hello, World!" application
@image html hello_windows7.png "\"Hello, World!\" application under Windows 7"
@include cpp11/hello.cpp

@subsection bootstrap Bootstrap application
@image html bootstrap_unity.png "Bootstrap application under Unity"
@include cpp11/bootstrap.cpp

@subsection widgets_screenshot Screenshots
@image html demo_unity.png "Demo application under Unity"
@image html demo_windows7.png "Demo application under Windows 7"
@image html demo_windows_xp.png "Demo application under Windows XP"
@image html demo_windows95.png "Demo application with Windows 95 theme"

@section overview Overview

@subsection initialization Initialization
Boost.UI library master include file is <boost/ui.hpp>
@snippet cpp11/snippet.cpp include
and this library uses @ref boost::ui namespace to hold all classes and functions.
@snippet cpp11/snippet.cpp namespace
Boost.UI requires GUI initialization and uninitialization, therefore you should use @ref boost::ui::entry() function to do it.
@snippet cpp11/snippet.cpp main

@subsection top_level_widgets Top level widgets (TLW)
@ref tlw (TLW) are widgets that are used to host other (child) widgets and they are controlled by OS window manager.
Basic TLW is @ref boost::ui::dialog. If you need @ref boost::ui::menu_bar or @ref boost::ui::status_bar support you should use @ref boost::ui::frame TLW.
@ref boost::ui::window is a base class for all (two) TLW classes.

@ref boost::ui::window::show_modal() class function displays TLW and waits while end user close TLW manually or @ref boost::ui::window::close() class function is called.
@snippet cpp11/snippet.cpp dialog

@ref boost::ui::frame with @ref boost::ui::menu_bar and @ref boost::ui::status_bar support:
@snippet cpp11/snippet.cpp frame

@subsection thread_safety Thread safety
Boost.UI is @b not thread safe library, so you should use @ref boost::ui::call_async() function to synchronize worker threads with main (GUI) thread.
However you can use @ref log in any thread, it is thread safe.

@subsection event_loops Event loops
Boost.UI has own event loops and you can't create other your own event loops inside main (GUI) thread without freezing GUI.
For example if you are using Boost.ASIO you should create other (worker) thread and synchronize it with main thread as described before.
Note that main thread is used to interact with user, not for long time calculations.

@subsection exception_safety Exception safety
Boost.UI catches exception inside @ref boost::ui::entry() and event handlers if you didn't catch it before.
And shows exception dialog window to the user.

@subsection event_handling Event handing
@ref widget have various event subscription functions (for example @ref boost::ui::button::on_press()).
If you pass callback function to it, this function will be called when event occurs (button press in this case).
Multiple subscription calls causes multiple event handlers calls,
i. e. event handler callback function isn't overrided on next event subscription call.

@subsection strings Strings
Boost.UI has own @ref boost::ui::uistring string class that simplifies conversion between native widget toolkit string classes and C++ Standard string classes.
Native string format could be ANSI, UTF-8, wchar_t etc.

@section src Source code
See <a href="https://github.com/kosenko/ui">source code (GitHub)</a>.
Read README.md file for build instructions and library details.

@see <a href="http://en.wikipedia.org/wiki/User_interface">User interface (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Graphical_user_interface">Graphical user interface (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Text-based_user_interface">Text-based user interface (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Widget_toolkit">Widget toolkit (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Look_and_feel">Look and feel (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Human_interface_guidelines">Human interface guidelines (Wikipedia)</a>

@example cpp11/beman.cpp Beman's challenge
@see <a href="http://isocpp.org/files/papers/n3791.html">N3791 Lightweight Drawing Library ideas</a>

@example cpp11/bootstrap.cpp Bootstrap code
@image html bootstrap_unity.png "Bootstrap application under Unity"

@example cpp11/demo.cpp Boost.UI C++11 demo

@example cpp11/hello.cpp C++11 "Hello, World!" application
@see <a href="http://en.wikipedia.org/wiki/%22Hello,_world!%22_program">"Hello, world!" program (Wikipedia)</a>
@image html hello_windows7.png "\"Hello, World!\" application under Windows 7"

@example cpp11/io2d.cpp Re-implemented examples from P0267 proposal (io2d library)
@example cpp11/minimal.cpp Minimal sample
@example cpp11/snippet.cpp Documentation snippets
@example cpp11/stroustrup.cpp Re-implemented Bjarne Stroustrup's GUI examples
@example asio_chat_client.cpp Boost.ASIO chat client example
@example chrono.cpp Boost.Chrono and std::chrono usage example
@example date_time.cpp Boost.Date_Time usage example

@example demo.cpp Boost.UI demo
@image html demo_unity.png "Demo application under Unity"
@image html demo_windows7.png "Demo application under Windows 7"
@image html demo_windows_xp.png "Demo application under Windows XP"
@image html demo_windows95.png "Demo application with Windows 95 theme"

@example font.cpp Boost.UI font usage example
@example filesystem.cpp Boost.Filesystem and std::filesystem file manager
@see <a href="http://en.wikipedia.org/wiki/File_manager">File manager (Wikipedia)</a>
@example geometry.cpp Boost.Geometry usage example
@example hello.cpp "Hello, World!" application
@see <a href="http://en.wikipedia.org/wiki/%22Hello,_world!%22_program">"Hello, world!" program (Wikipedia)</a>
@example interprocess.cpp Boost.Interprocess usage example
@example lexical_cast.cpp Boost.Lexical_Cast usage example
@example locale.cpp Boost.Locale usage example
@example native.cpp Native API usage example
@example random.cpp Boost.Random and std::random usage example
@see <a href="http://en.wikipedia.org/wiki/Pseudorandom_number_generator">Pseudorandom number generator (Wikipedia)</a>
@example regex.cpp Boost.Regex and std::regex usage example
@see <a href="http://en.wikipedia.org/wiki/Regular_expression">Regular expression (Wikipedia)</a>
@example sort.cpp Visualization of sorting algorithms
@see <a href="http://en.wikipedia.org/wiki/Sorting_algorithm">Sorting algorithm (Wikipedia)</a>
@example spirit.cpp Boost.Spirit usage example
@example stacktrace.cpp Boost.Stacktrace usage example
@example thread.cpp Boost.Thread and std::thread usage example
@see boost::ui::call_async
@see <a href="http://en.wikipedia.org/wiki/Thread_(computing)">Thread (Wikipedia)</a>
@example timer.cpp Boost.Timer usage example
@see boost::ui::on_timeout
@see <a href="http://en.wikipedia.org/wiki/Timer">Timer (Wikipedia)</a>
@example tokenizer.cpp Boost.Tokenizer usage example

@defgroup graphics Graphics
@see <a href="http://en.wikipedia.org/wiki/Computer_graphics">Computer graphics (Wikipedia)</a>

@defgroup widget Widgets

@defgroup command Command widgets
@ingroup widget

@defgroup io Data input-output widgets
@ingroup widget

@defgroup datetime Date and time pickers
@ingroup io

@defgroup strings Strings container widgets
@ingroup io

@defgroup text Text widgets
@see <a href="http://en.wikipedia.org/wiki/Text_box">Text box (Wikipedia)</a>
@ingroup io

@defgroup info Informational widgets
@ingroup widget

@defgroup log Logging
@ingroup info

@defgroup container Containers
@ingroup widget

@defgroup alert Alerts
@see <a href="http://en.wikipedia.org/wiki/Alert_dialog_box">Alert dialog box (Wikipedia)</a>
@ingroup container

@defgroup notify Notifications
@see <a href="http://en.wikipedia.org/wiki/Notification_area">Notification area (Wikipedia)</a>
@ingroup container

@defgroup prompt Prompts
@ingroup container

@defgroup tlw Top level widgets
@ingroup container

@defgroup layout Layouts
@see <a href="http://en.wikipedia.org/wiki/Layout_manager">Layout manager (Wikipedia)</a>

@defgroup event Events
Usage example:
@snippet cpp11/snippet.cpp event
@see <a href="http://en.wikipedia.org/wiki/Event_(computing)">Event (Wikipedia)</a>
@see <a href="http://www.w3.org/TR/uievents/">UI Events (W3C)</a>

@defgroup audio Audio
@see <a href="http://en.wikipedia.org/wiki/Sound">Sound (Wikipedia)</a>

@defgroup coord Coordinates
@see <a href="http://en.wikipedia.org/wiki/Cartesian_coordinate_system">
    Cartesian coordinate system (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Geometric_primitive">Geometric primitive (Wikipedia)</a>
@see <a href="http://www.w3.org/TR/geometry/">Geometry Interfaces (W3C)</a>

@defgroup locale Localization

@defgroup thread Thread support

@defgroup helper Helpers

*/

#endif // BOOST_UI_HPP
