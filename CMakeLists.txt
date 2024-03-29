cmake_minimum_required(VERSION 3.16.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(PakerGL)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(vendor/stb_image)

file(GLOB sources "src/*.cpp" "vendor/**/*.cpp")

add_executable(engine ${sources})

target_link_libraries(engine ${OPENGL_LIBRARIES} glfw GLEW::GLEW)

add_custom_command(
        TARGET engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res
)
