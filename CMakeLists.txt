cmake_minimum_required(VERSION 3.25)
project(cloth_sim)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)

add_executable(cloth_sim main.cpp environment.cpp environment.h event_data.cpp event_data.h cloth.cpp cloth.h point.cpp point.h stick.cpp stick.h SDL2_framerate.h SDL2_framerate.c)

include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cloth_sim PRIVATE ${SDL2_LIBRARIES})
