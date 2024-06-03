cmake_minimum_required(VERSION 2.8)
project(ChatServer)

# 配置编译选项，在原有的基础上添加
add_compile_options(-g -std=c++11)

# 设置目标文件目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定库文件路径
link_directories(/usr/lib64/mysql)

# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
# include_directories(${PROJECT_SOURCE_DIR}/test/test/include/server)
# include_directories(${PROJECT_SOURCE_DIR}/test/test/include/)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)


add_subdirectory(${PROJECT_SOURCE_DIR}/src)
# add_subdirectory(${PROJECT_SOURCE_DIR}/test)

