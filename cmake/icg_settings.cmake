# Build configuration file for "Intro to Graphics"
# Copyright (C) 2014 - LGG EPFL

#--- Tell CMake he'll be able to include ".cmake" configurations
# files in the folder where the current file is located
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

#--- CMake extension to load GLFW
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
add_definitions(${GLFW_DEFINITIONS})
if(NOT GLFW_FOUND)
    message(ERROR " GLFW not found!")
endif()

#--- GLEW (STATICALLY LINKED)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
# message(STATUS "HERE " ${GLEW_LIBRARIES})

#--- Wraps file deployments
macro(target_deploy_file MYTARGET FILEPATH)
    #--- FALSE: always use the "copy" just to avoid cross platform problems
    if(FALSE)
        #--- simple symbolic link
        execute_process(COMMAND ln -f -s ${CMAKE_SOURCE_DIR}/${FILEPATH} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        #--- windows likes to make my life difficult, copy them
        get_filename_component(FILENAME ${FILEPATH} NAME_WE)
        set(TARGET_NAME deployfile_${MYTARGET}_${FILENAME})
        set(TARGET_DIR ${CMAKE_CURRENT_BINARY_DIR})
        add_custom_target( # always out of date
            ${TARGET_NAME} ALL # always built
            SOURCES ${FILEPATH} # adds file to project manager
            COMMAND ${CMAKE_COMMAND} -E copy ${FILEPATH} ${TARGET_DIR}
            DEPENDS ${FILEPATH}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
endmacro()

#--- OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND) 
    message(ERROR " OPENGL not found!")
endif()

#--- On UNIX|APPLE you can do "make update_opengp" to update
if(CMAKE_HOST_UNIX)
    add_custom_target( update_opengp
        COMMAND rm -rf OpenGP
        COMMAND svn checkout https://github.com/OpenGP/OpenGP/trunk/src/OpenGP
        COMMAND rm -rf OpenGP/.svn
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/OpenGP/include
        COMMENT "Updating OpenGP ${CMAKE_SOURCE_DIR}")
endif()

#--- Make headers in common directory visible in the IDE
file(GLOB_RECURSE COMMON_DIR_HEADERS "${CMAKE_CURRENT_LIST_DIR}/*.h")
add_custom_target(common_headers SOURCES ${COMMON_DIR_HEADERS})

#--- Common headers/libraries for all the exercises
include_directories(${CMAKE_CURRENT_LIST_DIR})
SET(COMMON_LIBS ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} png)

