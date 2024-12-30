# src/CMakeLists.txt
# 将 src 目录下的所有 .cpp 文件添加到库中
file(GLOB SRC_FILES *.cpp)

# 创建一个静态库或共享库，视你的需求而定
add_library(src_lib ${SRC_FILES})

# 包含头文件路径，供其他目标使用
target_include_directories(src_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 添加编译选项（如果有特定需求）
target_compile_options(src_lib PRIVATE ${CMAKE_CXX_FLAGS})