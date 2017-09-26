Boost.UI build instructions
===========================
1. Download [Boost libraries](http://www.boost.org/) and
compile Build.Build b2 application using bootstrap script.
It is required to build Boost libraries.
2. Download [wxWidgets](http://www.wxwidgets.org/) 3.0+ library and build it.
Please build minimal sample and ensure that it starts properly (optional).
3. Download Boost.UI library and place it into boost-root/libs directory.
4. Build Boost.UI. It requires wxWidgets and must be compiled with additional flags under Linux:
 ```sh
 export WX_CONFIG=/path/to/wxWidgets-build/wx-config # wxWidgets 3.0+ wx-config script path
 ./b2 libs/ui/build/ cxxflags=-std=c++0x
 ./b2 libs/ui/test/ cxxflags=-std=c++0x
 ./b2 libs/ui/example/ cxxflags=-std=c++0x
 ./b2 libs/ui/example/cpp11/ cxxflags=-std=c++0x
 ```
 and under Windows using Visual C++ static build:
 ```bat
 set WXWIN=C:\path\to\wxWidgets
 b2 libs/ui/build/ link=static
 b2 libs/ui/test/ link=static
 b2 libs/ui/example/ link=static
 b2 libs/ui/example/cpp11/ link=static
 ```
