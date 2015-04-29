cmake_minimum_required(VERSION 2.8.4)
project(flaming_octo_avenger)

include(cmake/icg_settings.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES
    src/Attribute.cpp
    src/Attribute.hpp
    src/FrameBuffer.cpp
    src/FrameBuffer.hpp
    src/main.cpp
    src/Mountain.cpp
    src/Mountain.hpp
    src/OpenGLAttribute.cpp
    src/OpenGLAttribute.hpp
    src/OpenGLTexture.cpp
    src/OpenGLTexture.hpp
    src/OpenGLValue.cpp
    src/OpenGLValue.hpp
    src/OpenGLUniform.cpp
    src/OpenGLUniform.hpp
    src/Object.cpp
    src/Object.hpp
    src/OpenGL.hpp
    src/Plane.cpp
    src/Plane.hpp
    src/PerlinNoise.cpp
    src/PerlinNoise.hpp
    src/Program.cpp
    src/Program.hpp
    src/Shader.cpp
    src/Shader.hpp
    src/Skybox.cpp
    src/Skybox.hpp
    src/Texture.cpp
    src/Texture.hpp
    src/Triangle.cpp
    src/Triangle.hpp
    src/Uniform.cpp
    src/Uniform.hpp
    src/Util.cpp
    src/Util.hpp
    src/World.cpp
    src/World.hpp)

add_executable(flaming_octo_avenger ${SOURCE_FILES})
target_link_libraries(flaming_octo_avenger ${COMMON_LIBS})
