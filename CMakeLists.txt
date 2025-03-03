cmake_minimum_required(VERSION 3.30.0)
project(libtest)

# 添加MyLib库
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 链接静态库
link_libraries(MyLib)

# 不应该包含 MyLib 的源文件，因为这些文件已经被添加的 MyLib 的 CMakeLists.txt 文件处理了
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

#设置可执行文件的生成路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(test ${SRC})
