cmake_minimum_required(VERSION 3.10)

# set(CMAKE_GENERATOR "MinGW Makefiles")
set(CMAKE_BUILD_TYPE Debug)

project(one_weekend_ray_tracing)

if(EXISTS "${CMAKE_SOURCE_DIR}/src")
    add_subdirectory(src)
endif()

add_executable(one_weekend_ray_tracing main.cpp)

target_include_directories(one_weekend_ray_tracing PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(one_weekend_ray_tracing PRIVATE ${CMAKE_CXX_FLAGS})