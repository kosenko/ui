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
#include <boost/ui/checkbox.hpp>
#include <boost/ui/choice.hpp>
#include <boost/ui/color.hpp>
#include <boost/ui/color_io.hpp>
#include <boost/ui/combobox.hpp>
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
#include <boost/ui/groupbox.hpp>
#include <boost/ui/hyperlink.hpp>
#include <boost/ui/image.hpp>
#include <boost/ui/image_widget.hpp>
#include <boost/ui/label.hpp>
#include <boost/ui/layout.hpp>
#include <boost/ui/line.hpp>
#include <boost/ui/listbox.hpp>
#include <boost/ui/locale.hpp>
#include <boost/ui/log.hpp>
#include <boost/ui/menu.hpp>
#include <boost/ui/message.hpp>
#include <boost/ui/notebook.hpp>
#include <boost/ui/painter.hpp>
#include <boost/ui/panel.hpp>
#include <boost/ui/progressbar.hpp>
#include <boost/ui/slider.hpp>
#include <boost/ui/string.hpp>
#include <boost/ui/string_io.hpp>
#include <boost/ui/stringsbox.hpp>
#include <boost/ui/textbox.hpp>
#include <boost/ui/thread.hpp>
#include <boost/ui/web_widget.hpp>
#include <boost/ui/widget.hpp>
#include <boost/ui/window.hpp>

/** @mainpage

@tableofcontents

@section description Description

Boost.UI is a C++ User Interface Boost library that
- is cross-platform
- uses native system-provided widgets
- has STL-like and Boost-like API
- compatible with other Boost libraries
- supports modern C++11/14/17 features

@section hello "Hello, World!" application
@include cpp11/hello.cpp

@section bootstrap Bootstrap application
@include cpp11/bootstrap.cpp

@section src Source code
See <a href="https://github.com/kosenko/ui">source code (GitHub)</a>

@see <a href="http://en.wikipedia.org/wiki/User_interface">User interface (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Graphical_user_interface">Graphical user interface (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Text-based_user_interface">Text-based user interface (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Widget_toolkit">Widget toolkit (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Look_and_feel">Look and feel (Wikipedia)</a>
@see <a href="http://en.wikipedia.org/wiki/Human_interface_guidelines">Human interface guidelines (Wikipedia)</a>

@example cpp11/beman.cpp Beman's challenge
@see <a href="http://isocpp.org/files/papers/n3791.html">N3791 Lightweight Drawing Library ideas</a>
@example cpp11/bootstrap.cpp Bootstrap code
@example cpp11/demo.cpp Boost.UI C++11 demo
@example cpp11/hello.cpp C++11 "Hello, World!" application
@see <a href="http://en.wikipedia.org/wiki/%22Hello,_world!%22_program">"Hello, world!" program (Wikipedia)</a>
@example cpp11/snippet.cpp Documentation snippets
@example cpp11/stroustrup.cpp Re-implemented Bjarne Stroustrup's GUI examples
@example asio_chat_client.cpp Boost.ASI chat client example
@example chrono.cpp Boost.Chrono example
@example date_time.cpp Boost.Date_Time example
@example demo.cpp Boost.UI demo
@example font.cpp Boost.UI font example
@example filesystem.cpp Boost.Filesystem file manager
@see <a href="http://en.wikipedia.org/wiki/File_manager">File manager (Wikipedia)</a>
@example geometry.cpp Boost.Geometry example
@example hello.cpp "Hello, World!" application
@see <a href="http://en.wikipedia.org/wiki/%22Hello,_world!%22_program">"Hello, world!" program (Wikipedia)</a>
@example interprocess.cpp Boost.Interprocess example
@example lexical_cast.cpp Boost.Lexical_Cast example
@example locale.cpp Boost.Locale example
@example native.cpp Native API usage example
@example random.cpp Boost.Random example
@see <a href="http://en.wikipedia.org/wiki/Pseudorandom_number_generator">Pseudorandom number generator (Wikipedia)</a>
@example regex.cpp Boost.Regex example
@see <a href="http://en.wikipedia.org/wiki/Regular_expression">Regular expression (Wikipedia)</a>
@example sort.cpp Visualization of sorting algorithms
@see <a href="http://en.wikipedia.org/wiki/Sorting_algorithm">Sorting algorithm (Wikipedia)</a>
@example spirit.cpp Boost.Spirit example
@example stacktrace.cpp Boost.Stacktrace example
@example thread.cpp Boost.Thread example
@see boost::ui::call_async
@see <a href="http://en.wikipedia.org/wiki/Thread_(computing)">Thread (Wikipedia)</a>
@example timer.cpp Boost.Timer example
@see boost::ui::on_timeout
@see <a href="http://en.wikipedia.org/wiki/Timer">Timer (Wikipedia)</a>
@example tokenizer.cpp Boost.Tokenizer example

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
