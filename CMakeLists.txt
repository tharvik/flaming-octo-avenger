cmake_minimum_required(VERSION 2.8.4)
project(flaming_octo_avenger)

include(cmake/icg_settings.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES
    src/Attribute.cpp
    src/Attribute.h
    src/OpenGLValue.cpp
    src/OpenGLValue.hpp
    src/main.cpp
    src/Object.cpp
    src/Object.hpp
    src/OpenGL.hpp
    src/Plane.cpp
    src/Plane.hpp
    src/Program.cpp
    src/Program.hpp
    src/Shader.cpp
    src/Shader.hpp
    src/Triangle.cpp
    src/Triangle.hpp
    src/Util.cpp
    src/Util.hpp
    src/World.cpp
    src/Texture.cpp
    src/Texture.hpp
    src/Uniform.cpp
    src/Uniform.h
    src/World.hpp)

add_executable(flaming_octo_avenger ${SOURCE_FILES} src/OpenGLUniform.cpp src/OpenGLUniform.h src/OpenGLAttribute.cpp src/OpenGLAttribute.h)
target_link_libraries(flaming_octo_avenger ${COMMON_LIBS})
