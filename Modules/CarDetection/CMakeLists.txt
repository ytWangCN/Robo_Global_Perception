# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_LIB_SRCS 变量

aux_source_directory(. DIR_CARDETECTION)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


# 生成链接库

add_library (CarDetection ${DIR_CARDETECTION})
#target_link_libraries(CarDetection DeepSort)
#target_include_directories(CarDetection PUBLIC ../DeepSort/api)
target_include_directories(CarDetection PUBLIC include)

#target_include_directories(GyroScope PUBLIC ../../SerialPort/include)

