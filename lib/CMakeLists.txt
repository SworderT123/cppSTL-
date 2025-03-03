cmake_minimum_required(VERSION 3.30.0)

project(MyLib)

# 中文显示
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /source-charset:utf-8 /execution-charset:GBK")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    string(APPEND CMAKE_CXX_FLAGS " -fexec-charset=GBK")
  endif()
  
# 设置 C++ 标准为 C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MyLib_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(MyLib STATIC ${MyLib_SRC})