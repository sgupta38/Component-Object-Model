# //----------------------------------------------------------------------------------------------------------------------
# /*!
# @file CMakeLists.txt
#
# @author Sonu Gupta
#
# @date 2017-10-25 (original)
#
# @brief This is a CMake project file for the CMake builder application.
#        See web site "cmake.org" for more information.
# @note Currently this project has some issues with Visual Studio 15 compiler. Try building with other MSVC compilers.
# //----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.2)

project(FactoryApp)

## Source File
set(SOURCE FactoryApp.cpp)

## Solution 
if(WIN32)
    add_executable(FactoryApp ${SOURCE})
else()
    Message("This project is not applicable for Operating Systems other than Windows.")
endif()