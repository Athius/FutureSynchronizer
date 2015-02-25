# FutureSynchronizerLibrary

This project provides some templates to help parallelization.

Requires C++11 compiler (test with Clang (version 6) and Visual Studio 2013, doesn't work with Visual Studio 2012).

## How to compile:

~~~
mkdir build
cd build
cmake ..
make
~~~

## How to launch examples:

Inside build folder;

>./examples/returnValue/returnValue

>./examples/returnVoid/returnVoid


## Source tree:

~~~
  .
  ├── CMakeLists.txt
  ├── examples
  │   ├── CMakeLists.txt
  │   ├── returnValue
  │   │   ├── CMakeLists.txt
  │   │   ├── EnableCXX11.cmake
  │   │   ├── FindFutureSynchronizerLibrary.cmake
  │   │   └── main.cpp
  │   └── returnVoid
  │       ├── CMakeLists.txt
  │       ├── EnableCXX11.cmake
  │       ├── FindFutureSynchronizerLibrary.cmake
  │       └── main.cpp
  └── lib
      ├── factory
      │   └── FutureFactory.hxx
      ├── policy
      │   ├── Policy.hxx
  	  │   └── ResultPolicy.hxx
      └── thread
          └── FutureSynchronyzer.hxx
~~~
