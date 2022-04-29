aux_source_directory(. mylib) #查找当前目录下的tool1相关文件
find_package(OpenCV REQUIRED)
find_package(Threads)

include_directories("./")
add_library(mylib ${mylib})   #将他们编译为一个叫tool1lib的文件
target_link_libraries(mylib ${OpenCV_LIBS}  ${CMAKE_THREAD_LIBS_INIT})
