# CMake 最低版本号要求

cmake_minimum_required (VERSION 3.5)


# 项目信息

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


add_library(Referee STATIC referee.cpp refereeio.cpp ./SerialPort/SerialPort.cpp)

# 添加链接库

target_link_libraries(Referee ${OpenCV_LIBS})
target_include_directories(Referee PUBLIC include)
target_include_directories(Referee PUBLIC SerialPort/include)


