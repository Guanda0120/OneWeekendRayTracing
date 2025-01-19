# src/materials/CMakeLists.txt

# 设置材料模块的源文件
set(MATERIALS_SRC_FILES
    material.cpp
    lambertian.cpp
    metal.cpp
)

# 创建静态库 materials_lib
add_library(materials_lib STATIC ${MATERIALS_SRC_FILES})

# 包含头文件路径
# PUBLIC: 允许 materials_lib 的依赖者也能访问这些路径
target_include_directories(materials_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include/materials
)

# 让 materials_lib 依赖 src_lib
target_link_libraries(materials_lib PUBLIC src_lib)
