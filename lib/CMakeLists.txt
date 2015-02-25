cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

set(PROJECT_OUTPUT_NAME FutureSynchronyzer)

set(PROJECT_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

set(PROJECT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_SOURCE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE source_files
                  *.hxx)

include(Project)

#try_build_library()

include(Package)

# Add the targets to create your binary application package and your source application package
try_build_package()

include(Documentation)

# Add the targets to create your documentation (html, latex and pdf if you have Doxygen, Latex and pdflatex)
try_build_documentation()
