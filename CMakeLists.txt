cmake_minimum_required(VERSION 3.19.0-rc1)
project("LineSimp" VERSION 1.0.0)

find_package(CGAL CONFIG REQUIRED)

add_executable("${PROJECT_NAME}" code/main.cpp code/math_util.cpp code/subdiv_simplification.cpp)

target_link_libraries("${PROJECT_NAME}" PRIVATE CGAL::CGAL)
