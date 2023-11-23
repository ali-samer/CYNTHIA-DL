cmake_minimum_required(VERSION 3.2)

# Here, a project declaration is made with the name "Cynthia-DL" and version "0.1.0".
# CMake will use this to create variables <PROJECT-NAME>_SOURCE_DIR, <PROJECT-NAME>_BINARY_DIR, and others. Additionally, project-specific build properties can be set.
project(Cynthia-DL VERSION 0.1.0 )


########################################################
## Compile Commands and Output Directories
########################################################

# This line enables the generation of a JSON compilation database (compile_commands.json) file.
# This file can be used by various tools for code completion, linting, or more advanced code understanding.
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

# This line sets the output directory for runtime target files to <build directory>/bin.
# Runtime target files are executable programs and/or DLLs that are part of a project's build results
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# This line sets the runtime path (rpath) for the install tree.
# RPATH indicates where to look for shared libraries in runtime. This is especially useful when the libraries are not installed in standard system directories.
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")



########################################################
## Standalone Build Check:
########################################################

# This block of code checks if the current source directory equals the top level source directory.
# If it is the same, it means the project is being built as a standalone project, not a subproject.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

    # Setting a flag (CYDL_STANDALONE) to indicate that the project is being built as a standalone project
    set(CYDL_STANDALONE ON)

    # In case of building as standalone, extra tooling functionality is included.
    # These may set certain project-specific parameters, handle requirements, and configuration for the build types
    include(cmake/GitVars.cmake)
    include(cmake/BuildTypes.cmake)
else ()

    # If the project is not being built as a standalone project (i.e., it is a subproject), the flag is set to OFF
    set(CYDL_STANDALONE OFF)
endif ()

option(CYDL_STANDALONE "Cynthia-DL: build standalone" ${CYDL_STANDALONE})

########################################################
## Build Options:
########################################################

# We check if we're building with MinGW (a development environment for Windows).
# If we are, we default to not building shared libraries.
if (MINGW)
    set(BULD_SHARED_LIBS_DEFAULT OFF)
else ()
    # If we're not using this environment, we do default to building shared libraries.
    set(BUILD_SHARED_LIBS_DEFAULT ON)
endif ()

# The BUILD_SHARED_LIBS option controls whether to build shared libraries.
# If not set manually by the user, it will adopt the default value we defined above based on the toolchain.
# The special variable BUILD_SHARED_LIBS is a standard variable in CMake, which instructs CMake to build shared libraries if ON, or static libraries if OFF.
option(BUILD_SHARED_LIBS "Cynthia-DL: build shared libs" ${BUILD_SHARED_LIBS_DEFAULT})


# Declare 'CYDL_ALL_WARNINGS' as an option. If enabled, it will turn on all compiler warnings for the Cynthia-DL project.
# Such an option is often used during development phase to catch any potential problems in the code.
option(CYDL_ALL_WARNINGS "Cynthia-DL: enable all compiler warnings" ON)

# Declare 'CYDL_ALL_WARNINGS_3RD_PARTY' as an option. If enabled, it will turn on all compiler warnings even for the 3rd party libraries used in the Cynthia-DL project.
# Typically, warnings for 3rd party libraries are disabled because we usually don't modify those codes, and warnings for them can pollute the warning log.
option(CYDL_ALL_WARNINGS_3RD_PARTY "Cynthia-DL: enable all compiler warnings in 3rd party libs" OFF)

# Declare various "sanitizer" options. When enabled, they activate corresponding sanitizers that help find runtime errors.
# 'CYDL_SANITIZE_THREAD' enables the thread sanitizer (detects data races).
# 'CYDL_SANITIZE_ADDRESS' enables the address sanitizer (detects memory errors).
# 'CYDL_SANITIZE_UNDEFINED' enables the undefined behavior sanitizer (detects undefined behavior occurrences).
option(CYDL_SANITIZE_THREAD "Cynthia-DL: enable thread sanitizer" OFF)
option(CYDL_SANITIZE_ADDRESS "Cynthia-DL: enable address sanitizer" OFF)
option(CYDL_SANITIZE_UNDEFINED "Cynthia-DL: enable undefined sanitizer" OFF)












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
