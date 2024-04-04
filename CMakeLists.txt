cmake_minimum_required(VERSION 3.27)
project(p2_forest_15_03_24)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(p2_forest_15_03_24 main.cpp flower/flower.cpp bee/bee.cpp others/world.cpp hornet/hornet.cpp entity/entity.cpp
        others/utils.cpp
        hive/hive.cpp
        hive/beehive.cpp
        hive/hornethive.cpp
        others/globals.cpp
)

include_directories("C:/SFML/include")
target_link_libraries(p2_forest_15_03_24 sfml-graphics sfml-window sfml-system)