# 设置材料模块的源文件
set(MATERIALS_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/material_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/material.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lambertian.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/metal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dielectric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/checker_texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solid_color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/image_texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/perlin_noise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/perlin_texture.cpp
)

set(MATERIALS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/materials)

# 将变量设置为 PARENT_SCOPE，使其可供上级目录使用
set(MATERIALS_SRC_FILES ${MATERIALS_SRC_FILES} PARENT_SCOPE)
set(MATERIALS_INCLUDE_DIR ${MATERIALS_INCLUDE_DIR} PARENT_SCOPE)

# 调试信息
message(STATUS "MATERIALS_SRC_FILES: ${MATERIALS_SRC_FILES}")
message(STATUS "MATERIALS_INCLUDE_DIR: ${MATERIALS_INCLUDE_DIR}")