// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_UI_NATIVE_WINMAIN_CPP
#define BOOST_UI_NATIVE_WINMAIN_CPP

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
#if defined(BOOST_UI_SOURCE) && !defined(BOOST_UI_DYN_LINK) \
|| !defined(BOOST_UI_SOURCE) && !defined(BOOST_UI_STATIC_LINK)

#include <windows.h>

extern "C" int main(int, char**);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _MSC_VER
    return main(__argc, __argv);
#else
    // TODO
    char* argv[] = { "" };
    return main(1, argv);
#endif
}

#endif
#endif

#endif // BOOST_UI_NATIVE_WINMAIN_CPP
