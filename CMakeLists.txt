cmake_minimum_required(VERSION 3.27)
project(p2_forest_15_03_24)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(p2_forest_15_03_24 main.cpp flower.cpp bee.cpp world.cpp hornet.cpp entity.cpp utils.cpp hive.cpp beehive.cpp hornethive.cpp)

if(SFML_FOUND)
    target_link_libraries(p2_forest_15_03_24 sfml-graphics sfml-window sfml-system)
endif()
