cmake_minimum_required(VERSION 2.8)
project( a.out )
find_package( OpenCV REQUIRED )
add_executable( a.out test.cpp )
target_link_libraries( a.out /usr/local/include/opencv4 /usr/local/lib opencv_core opencv_imgcodecs opencv_highgui )
set(CMAKE_CXX_FLAGS "-Wall -g -fsanitize=undefined,address -std=c++17")
