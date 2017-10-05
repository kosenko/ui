Boost.UI
========

Boost.UI is a C++ User Interface Boost library that
* is cross-platform
* uses native system-provided widgets
* has STL-like and Boost-like API
* compatible with other Boost libraries
* supports modern C++11/14/17 features

[Documentation](https://kosenko.github.io/boost.ui/)

### Contents

* **build** - Build scripts and instructions
* **doc** - Documentation generator scripts
* **example** - Examples
  * example/hello.cpp - **"Hello, world!"** application
  * example/asio_chat_client.cpp - **Boost.ASIO** chat client example
  * example/chrono.cpp - **Boost.Chrono** usage example
  * example/date_time.cpp - **Boost.Date_Time** usage example
  * example/font.cpp - Font usage example
  * example/filesystem.cpp - **Boost.Filesystem** usage example
  * example/geometry.cpp - **Boost.Geometry** usage example
  * example/interprocess.cpp - **Boost.Interprocess** usage example
  * example/lexical_cast.cpp - **Boost.Lexical_Cast** usage example
  * example/locale.cpp - **Boost.Locale** usage example
  * example/random.cpp - **Boost.Random** usage example
  * example/regex.cpp - **Boost.Regex** usage example
  * example/sort.cpp - Visualization of **sorting algorithms**
  * example/stacktrace.cpp - **Boost.Stacktrace** usage example
  * example/thread.cpp - **Boost.Thread** usage example
  * example/timer.cpp - **Boost.Timer** usage example
  * example/tokenizer.cpp - **Boost.Tokenizer** usage example
* **example/cpp11** - C++11 Examples
  * example/cpp11/hello.cpp - C++11 **"Hello, world!"** application
  * example/cpp11/beman.cpp - Beman's challenge
  * example/cpp11/stroustrup.cpp - Re-implemented GUI examples
from "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
* **include** - Interface headers with documentation
* **src** - Source code
* **test** - Unit tests

### Build instructions and dependencies

See [build instructions](build/README.md).

Tested compilers: GCC 5.4.0, Clang 3.8.0, Visual C++ 9.0, 14.0.

Boost.UI depends on Boost.Config, Boost.Core, Boost.Function, Boost.Bind, Boost.Move, Boost.Optional, Boost.Tribool, Boost.Range and wxWidgets libraries.
Also optionally Boost.Chrono and Boost.Date_Time could be used.
Note that corresponding classes from C++11 Standard also could be used with Boost.UI if available.

### License

Distributed under the [Boost Software License, Version 1.0](http://boost.org/LICENSE_1_0.txt).
