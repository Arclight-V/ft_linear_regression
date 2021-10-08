cmake_minimum_required(VERSION 3.20)
project(testEigen)

set(CMAKE_CXX_STANDARD 20)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(testEigen main.cpp)
target_link_libraries(testEigen Eigen3::Eigen)