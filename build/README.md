Boost.UI build instructions
===========================
1. Download [Boost libraries](http://www.boost.org/) and
compile Build.Build b2 application using bootstrap script, for example:

```sh
sudo ./bootstrap.sh --prefix=/usr/local                            ±[●●][master]
```

It is required to build Boost libraries.
2. Download [wxWidgets](http://www.wxwidgets.org/) 3.0+ library and build it.
Optionally please build minimal sample and ensure that it starts properly.
Under Linux you can just install libwxgtk-webview3.0-dev package instead of manual build.
3. Download Boost.UI library and place it into boost-root/libs directory.
4. Build Boost.UI. Under Linux specify path to wx-config script if you built wxWidgets manually:
 ```sh
 export WX_CONFIG=/path/to/wxWidgets-build/wx-config # wxWidgets 3.0+ wx-config script path
 ```
 Build Boost.UI under Linux:
 ```sh
 ./b2 libs/ui/build/ cxxflags=-std=c++0x
 ./b2 libs/ui/test/ cxxflags=-std=c++0x
 ./b2 libs/ui/example/ cxxflags=-std=c++0x
 ./b2 libs/ui/example/cpp11/ cxxflags=-std=c++0x
 ```
 Build Boost.UI under Windows using Visual C++ static build:
 ```bat
 set WXWIN=C:\path\to\wxWidgets
 b2 libs/ui/build/ link=static
 b2 libs/ui/test/ link=static
 b2 libs/ui/example/ link=static
 b2 libs/ui/example/cpp11/ link=static
 ```

If you want to install ui with all other libs:

``` sh
sudo  ./b2 install                                            ±[●●][master]
```

### FAQ

#### if `undefined refernce` occur and is 

##### 1. about with `wx********`

Please try add `wx-config --cxxflags` `wx-config --libs` when linking(compiling)

##### 2. about boost


Please try add `-lboost_****` when linking(compiling), e.g., `-lboost_ui`

#### ./a.out: error while loading shared libraries: libboost_filesystem.so.1.68.0: cannot open shared object file: No such file or directory

That's because the library cannot befound. You can find this lib manually with mlocate:

``` sh
locate libboost_filesystem
```

if the result is `/usr/local/lib/libboost_filesystem.so.1.68.0`

just add `export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH` to your `.zshrc`/`.bashrc` and so on.
