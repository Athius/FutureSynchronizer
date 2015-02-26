cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

find_package(FutureSynchronizerLibrary REQUIRED)

include(EnableCXX11)

project(returnValue CXX)

find_package (Threads)

set(ADDITIONAL_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

set(PROJECT_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

include(Project)

# Set the name of your project and you want the parent name as prefix
# set_project_with_parent_name_prefix(returnValue CXX)

# Add the target to build your application
try_build_application()

include(Package)

# Add the targets to create your binary application package and your source application package
try_build_package()

include(Documentation)

# Add the targets to create your documentation (html, latex and pdf if you have Doxygen, Latex and pdflatex)
try_build_documentation()
