Boost.UI
========

Boost.UI is a C++ User Interface (GUI) Boost library that
* is cross-platform
* uses native system-provided widgets
* has STL-like and Boost-like API
* compatible with other Boost libraries
* supports modern C++11/14/17 features

[![Licence](https://img.shields.io/badge/license-boost-4480cc.svg)](http://www.boost.org/LICENSE_1_0.txt)
[![Build Status](https://travis-ci.org/kosenko/ui.svg?branch=master)](https://travis-ci.org/kosenko/ui)
[![Build status](https://ci.appveyor.com/api/projects/status/yv9f8pw2qcfsau4i/branch/master?svg=true)](https://ci.appveyor.com/project/kosenko/ui/branch/master)

### Documentation

Latest development documentation is available [online](https://kosenko.github.io/boost.ui/).

### Contents

* **build** - Build scripts and instructions
* **doc** - Documentation generator scripts
* **example** - Examples
  * example/hello.cpp - **"Hello, world!"** application
  * example/asio_chat_client.cpp - **Boost.ASIO** chat client example
  * example/chrono.cpp - **Boost.Chrono** and **std::chrono** usage example
  * example/date_time.cpp - **Boost.Date_Time** usage example
  * example/font.cpp - Font usage example
  * example/filesystem.cpp - **Boost.Filesystem** and **std::filesystem** file manager
  * example/geometry.cpp - **Boost.Geometry** usage example
  * example/interprocess.cpp - **Boost.Interprocess** usage example
  * example/lexical_cast.cpp - **Boost.Lexical_Cast** usage example
  * example/locale.cpp - **Boost.Locale** usage example
  * example/random.cpp - **Boost.Random** and **std::random** usage example
  * example/regex.cpp - **Boost.Regex** and **std::regex** usage example
  * example/sort.cpp - Visualization of **sorting algorithms**
  * example/stacktrace.cpp - **Boost.Stacktrace** usage example
  * example/thread.cpp - **Boost.Thread** and **std::thread** usage example
  * example/timer.cpp - **Boost.Timer** usage example
  * example/tokenizer.cpp - **Boost.Tokenizer** usage example
* **example/cpp11** - C++11 Examples
  * example/cpp11/hello.cpp - C++11 **"Hello, world!"** application
  * example/cpp11/beman.cpp - [Beman's challenge](https://isocpp.org/files/papers/n3791.html)
  * example/cpp11/stroustrup.cpp - Re-implemented GUI examples
from ["Programming -- Principles and Practice Using C++"](http://www.stroustrup.com/programming.html)
by Bjarne Stroustrup
  * example/cpp11/io2d.cpp - Re-implemented examples from
[P0267 proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0267r6.pdf) (io2d library)
  * example/cpp11/snippet.cpp - Documentation snippets
* **include** - Interface headers with documentation
* **src** - Source code
* **test** - Unit tests

### Build instructions and dependencies

See [build instructions](build/README.md).

Tested compilers: GCC 5.4.0, Clang 3.8.0, Visual C++ 9.0 (2008), 14.0 (2015), Travis CI and AppVeyor compilers.

Boost.UI depends on Boost.Config, Boost.Core, Boost.Function, Boost.Bind, Boost.Move, Boost.Optional, Boost.Tribool, Boost.Range and wxWidgets libraries.
Also optionally Boost.Chrono and Boost.Date_Time could be used.
Note that corresponding classes from C++11 Standard also could be used with Boost.UI if available.

Boost.UI is a binary library (not header-only) and must be built separately.

### License

Distributed under the [Boost Software License, Version 1.0](http://boost.org/LICENSE_1_0.txt).
