cmake_minimum_required(VERSION 2.8)   #cmake版本最低要求
project( DisplayImage )    #工程名
find_package( OpenCV REQUIRED )    #查找openCV包用的,不许修改
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DisplayImage demo.cpp )#添加源代码(工程项目名，源代码)
target_link_libraries( DisplayImage ${OpenCV_LIBS} )#库
