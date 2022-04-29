cmake_minimum_required(VERSION 3.0.0)
project(camera VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(OpenCV REQUIRED)
find_package(Threads)

include_directories("./src")
add_subdirectory(src)   

add_executable(camera main.cpp)

target_link_libraries(camera ${OpenCV_LIBS}  ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(camera mylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
