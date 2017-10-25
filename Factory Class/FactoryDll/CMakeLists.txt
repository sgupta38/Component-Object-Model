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

project(FactoryDll)

## Source File
set(SOURCE interface.cpp interface.h interfaces.def)

## Solution 
if(WIN32)
   add_library(FactoryDll SHARED ${SOURCE})
   set_source_files_properties(interfaces.def PROPERTIES GENERATED TRUE)
else()
    Message("This project is not applicable for Operating Systems other than Windows.")
endif()

