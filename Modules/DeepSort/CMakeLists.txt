# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_LIB_SRCS 变量

AUX_SOURCE_DIRECTORY(./errmsg DIR_SRCS_errmsg)
AUX_SOURCE_DIRECTORY(./thirdPart DIR_SRCS_hungarianoper)
AUX_SOURCE_DIRECTORY(./thirdPart/munkres DIR_SRCS_munkres)
AUX_SOURCE_DIRECTORY(./thirdPart/munkres/adapters DIR_SRCS_munkres_adapters)
AUX_SOURCE_DIRECTORY(./matching DIR_SRCS_matching)
AUX_SOURCE_DIRECTORY(./feature DIR_SRCS_feature)
AUX_SOURCE_DIRECTORY(./common DIR_SRCS_common)
AUX_SOURCE_DIRECTORY(./api DIR_SRCS_api)
AUX_SOURCE_DIRECTORY(./common DIR_SRCS_common)
AUX_SOURCE_DIRECTORY(./image DIR_SRCS_image)



include_directories(
./errmsg
./thirdPart
./thirdPart/Eigen
./thirdPart/munkres
./thirdPart/munkres/adapters
./matching
./feature
./common
./api
./image
./common
)


find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


# 生成链接库


add_library(DeepSort SHARED 
${DIR_SRCS_errmsg} 
${DIR_SRCS_hungarianoper} 
${DIR_SRCS_munkres} 
${DIR_SRCS_munkres_adapters} 
${DIR_SRCS_feature} 
${DIR_SRCS_matching} 
${DIR_SRCS_api}
)

target_include_directories(DeepSort PUBLIC api)
target_include_directories(DeepSort PUBLIC common)
target_include_directories(DeepSort PUBLIC darkSrc)
target_include_directories(DeepSort PUBLIC errmsg) 
target_include_directories(DeepSort PUBLIC feature)
target_include_directories(DeepSort PUBLIC image)
target_include_directories(DeepSort PUBLIC matching)
target_include_directories(DeepSort PUBLIC thirdPart)

#target_include_directories(GyroScope PUBLIC ../../SerialPort/include)