# 如果源文件太多，可以使用aux_source_directory把.指定路径下的所有源文件放入变量名SRC_LIST里面
aux_source_directory(. SRC_LIST)

# 表示生成可执行文件server，由SRC_LIST变量所定义的源文件编译而来
add_executable(test ${SRC_LIST})
# 表示server这个目标程序，需要连接muduo_net muduo_base pthread这三个库文件
target_link_libraries(test muduo_net muduo_base pthread)