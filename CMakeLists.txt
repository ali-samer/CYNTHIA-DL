cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)
project(CYNTHIA-DL)


#set(xtl_DIR /opt/homebrew/Caskroom/mambaforge/base/pkgs/xtl-0.7.5-hffc8910_0/share/cmake/xtl)

if(xtl_FOUND)
    message(STATUS "xtl: ${xtl_DIR}")
endif ()
set(SOURCE_DIRS
        "${CMAKE_SOURCE_DIR}/src/Core"
        "${CMAKE_SOURCE_DIR}/src/Data"
        "${CMAKE_SOURCE_DIR}/src/Layers"
        "${CMAKE_SOURCE_DIR}/src/Models"
        "${CMAKE_SOURCE_DIR}/src/Objectives"
        "${CMAKE_SOURCE_DIR}/src/Optimizers"
        "${CMAKE_SOURCE_DIR}/src/Activations"
)

set(SRC_FILES "")

foreach(SOURCE_DIR ${SOURCE_DIRS})
    file(GLOB SOURCE_FILES_IN_DIR
            "${SOURCE_DIR}/*.cpp"
            "${SOURCE_DIR}/*.c"
    )
    list(APPEND SRC_FILES ${SOURCE_FILES_IN_DIR})
endforeach()
message("src files: ${SRC_FILES}")

include_directories(include)
include_directories(vendor/src/xtl/include)
include_directories(vendor/src/xtensor/include)
include_directories(vendor/src)


add_subdirectory(vendor/src/xtensor)

add_executable(cynthia Sandbox/src/main.cpp ${SRC_FILES})
