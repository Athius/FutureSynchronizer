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

Two examples are provided: <i>returnValue</i> and <i>returnVoid</i>.

<i>returnValue</i> shows you how to implement a function with a return value and
get the result at the end of all the calculation.

<i>returnVoid</i> shows you how to implement a function with no return value.

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
