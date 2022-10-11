# CMake 最低版本号要求

#cmake_minimum_required (VERSION 2.8)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE Release)

# 项目信息

project (Radar LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)
option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)


find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


find_package(ZED 3 REQUIRED)

include_directories(${ZED_INCLUDE_DIRS})


find_package(CUDA ${ZED_CUDA_VERSION} EXACT REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})

find_package(BehaviorTreeV3)
include_directories(${BehavoirTreeV3_INCLUDE_DIRS})
find_package(Boost)

include_directories(Parameter/include)

link_directories(${ZED_LIBRARY_DIR})
link_directories(${OpenCV_LIBRARY_DIRS})
link_directories(${CUDA_LIBRARY_DIRS})
#link_directories("./build/Modules/DeepSort/")

# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_SRCS 变量

aux_source_directory(. DIR_SRCS)

# 添加 math 子目录

add_subdirectory(Modules/CarDetection)
add_subdirectory(Modules/Mapping)
add_subdirectory(Modules/Preprocess)
add_subdirectory(Modules/ZEDConfigure)
add_subdirectory(Referee)
add_subdirectory(Modules/BTree)
add_subdirectory(Parameter)
add_subdirectory(RMVideoCapture)
#add_subdirectory(Modules/DeepSort)
# 指定生成目标
#add_executable(Radar main.cpp)
#add_definitions(-std=c++14 -O3)
set(PROJECT_SOURCES
       main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        camdialog.cpp
        camdialog.h
        camdialog.ui
        fileselect.h
        fileselect.cpp
        fileselect.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Radar
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Radar SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Radar
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 添加链接库
if (LINK_SHARED_ZED)
    SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY})
else()
    SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARY})
endif()

#target_link_libraries(Radar libDeepSort.so)
target_link_libraries(Radar ${OpenCV_LIBS} ${ZED_LIBS})
target_link_libraries(Radar Parameter)
target_link_libraries(Radar CarDetection)
target_link_libraries(Radar Mapping)
target_link_libraries(Radar Preprocess)
target_link_libraries(Radar ZEDConfigure)
target_link_libraries(Radar RMVideoCapture)
target_link_libraries(Radar BTree)
target_link_libraries(Radar Referee)
target_link_libraries(Radar Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Radar Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(Radar BT::behaviortree_cpp_v3 )
set_property(TARGET Radar PROPERTY CXX_STANDARD 14)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/./Loadings)

