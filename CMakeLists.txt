cmake_minimum_required(VERSION 3.10)

# set(CMAKE_GENERATOR "MinGW Makefiles")
set(CMAKE_BUILD_TYPE Debug)

project(one_weekend_ray_tracing)

# 指定 PNG 和 ZLIB 包的路径
set(PNG_INCLUDE_DIRS "C:/Program Files (x86)/libpng/include/libpng16")
set(ZLIB_INCLUDE_DIRS "C:/Program Files (x86)/zlib/include")

# 设置库的路径
set(PNG_LIBRARIES "C:/Program Files (x86)/libpng/lib/libpng16.dll.a")
set(ZLIB_LIBRARIES "C:/Program Files (x86)/zlib/lib/libzlibstatic.a")

add_subdirectory(src)

add_executable(one_weekend_ray_tracing main.cpp)

target_include_directories(one_weekend_ray_tracing PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${PNG_INCLUDE_DIRS} 
    ${ZLIB_INCLUDE_DIRS} 
    )

target_link_libraries(one_weekend_ray_tracing PRIVATE materials_lib src_lib  ${PNG_LIBRARIES} ${ZLIB_LIBRARIES})
