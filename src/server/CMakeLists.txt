# 设置源文件变量
aux_source_directory(. SRC_LIST)
# set(SRC_LIST main.cpp chatserver.cpp)

# 生成可执行文件
add_executable(server ${SRC_LIST})
# 配置目标文件链接所需的库
target_link_libraries(server muduo_net muduo_base pthread)
