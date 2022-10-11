# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_LIB_SRCS 变量

aux_source_directory(. DIR_BTREE)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
find_package(BehaviorTreeV3)
include_directories(${BehavoirTreeV3_INCLUDE_DIRS})

# 生成链接库

add_library (BTree ${DIR_BTREE})

target_include_directories(BTree PUBLIC include)
target_include_directories(BTree PUBLIC ../../Referee)
target_include_directories(BTree PUBLIC ../../Referee/SerialPort/include)
