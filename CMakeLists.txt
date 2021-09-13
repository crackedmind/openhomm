cmake_minimum_required(VERSION 3.20)

project(openhomm VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_SYSROOT_FLAG_CODE "list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS ixx cppm)")

set(ZLIB_ENABLE_TESTS OFF)
add_subdirectory(thirdparty/zlib-ng)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_GLFW_INSTALL OFF)
add_subdirectory(thirdparty/glfw)

message("CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")

set(OPENHOMM_SRC 
    src/math/math-vector.cppm
    src/math/math-matrix.cppm
    src/math/math.cpp
    src/math/math.cppm

    src/main.cpp
    src/application.cppm
)

set(OPENHOMM_HEADER_UNITS
    ${GLFW_SOURCE_DIR}/include/GLFW/glfw3.h
)

set(OPENHOMM_MODULES
    modules/glfw.cppm
)

add_executable(openhomm ${OPENHOMM_SRC} ${OPENHOMM_MODULES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${OPENHOMM_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${OPENHOMM_MODULES})

target_compile_features(openhomm PUBLIC cxx_std_23)
target_link_libraries(openhomm PUBLIC glfw zlib opengl32)
#target_include_directories(openhomm PUBLIC src)
target_compile_options(openhomm PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /permissive- /Z7 /MP /Bt+>)
