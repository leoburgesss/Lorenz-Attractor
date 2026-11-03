cmake_minimum_required(VERSION 3.16)
project(lorenz_attracotor CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Lorenz 
  src/main.cpp
  src/render/render.cpp
  src/render/render.h
)

target_include_directories(Lorenz PRIVATE src)

target_link_libraries(Lorenz PRIVATE glfw GLEW::GLEW OpenGL::GL)
