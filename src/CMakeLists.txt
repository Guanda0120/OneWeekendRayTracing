# src/CMakeLists.txt
# 将 src 目录下的所有 .cpp 文件添加到库中
# 指定 PNG 和 ZLIB 包的路径
set(PNG_INCLUDE_DIRS "C:/Program Files (x86)/libpng/include/libpng16")
set(ZLIB_INCLUDE_DIRS "C:/Program Files (x86)/zlib/include")

# 设置库的路径
set(PNG_LIBRARIES "C:/Program Files (x86)/libpng/lib/libpng16.dll.a")
set(ZLIB_LIBRARIES "C:/Program Files (x86)/zlib/lib/libzlibstatic.a")

set(SRC_FILES
    camera.cpp
    canvas.cpp
    color.cpp
    image.cpp
    ray.cpp
    vec3.cpp
    sphere.cpp
    hittable_list.cpp
)

# 创建一个静态库或共享库，视你的需求而定
add_library(src_lib STATIC ${SRC_FILES})

# 包含头文件路径，供其他目标使用
target_include_directories(src_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    )

target_include_directories(src_lib PRIVATE
    ${PNG_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    )

target_link_libraries(src_lib PRIVATE
    ${PNG_LIBRARIES}
    ${ZLIB_LIBRARIES}
    )

message(STATUS "PNG_INCLUDE_DIR: ${PNG_INCLUDE_DIRS}")
message(STATUS "ZLIB_INCLUDE_DIR: ${ZLIB_INCLUDE_DIRS}")
message(STATUS "PNG_LIBRARIES: ${PNG_LIBRARIES}")
message(STATUS "ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")
