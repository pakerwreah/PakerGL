cmake_minimum_required(VERSION 3.16.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(PakerGL)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(vendor)

file(GLOB sources "src/*.cpp")

add_executable(engine ${sources})

target_link_libraries(engine ${OPENGL_LIBRARIES} glfw GLEW::GLEW)