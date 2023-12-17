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


########################################################
## Building Tests and Examples:
########################################################

option(CYDL_BUILD_TESTS "Cynthia-DL: build tests" ${CYDL_STANDALONE})
option(CYDL_BUILD_EXAMPLES "Cynthia-DL: build example" ${CYDL_STANDALONE})


########################################################
## Cynthia-DL Performance Configuration Options:
########################################################

# CYDL_TEST_COVERAGE: This option enables the collection of test coverage data. If set to ON,
# the generated build system will include configurations for collecting test coverage data
# using compatible tools. If set to OFF (default), no test coverage data will be collected.
option(CYDL_TEST_COVERAGE "Cynthia-DL: enable test coverage" OFF)

# CYDL_PERF: This option enables performance timing measurements within the Cynthia-DL library.
# If set to ON, the library will include code for measuring execution time of specific operations.
# If set to OFF (default), no performance timing measurements will be included.
option(CYDL_PERF "Cynthia-DL: enable perf timings" OFF)

# CYDL_NO_ACCELERATE: This option controls the usage of the Accelerate framework on macOS. If set to ON,
# the Accelerate framework is disabled and Cynthia-DL will not use it. If set to OFF (default),
# the library may use the Accelerate framework if available.
option(CYDL_NO_ACCELERATE "Cynthia-DL: disable Accelerate framework" OFF)

# CYDL_OPENBLAS: This option controls the usage of the OpenBLAS library for BLAS routines.
# If set to ON, OpenBLAS will be used. If set to OFF (default), the library will use the BLAS
# implementation available on the system if any.
option(CYDL_OPENBLAS "Cynthia-DL: use OpenBLAS" OFF)

# CYDL_CLBLAST: This option controls the usage of the clBLAST library for BLAS routines on OpenCL devices.
# If set to ON, clBLAST will be used. If set to OFF (default), the library will not use clBLAST
# even if it is available.
option(CYDL_CLBLAST "Cynthia-DL: clBLAST" OFF)

# CYDL_CUBLAS: This option controls the usage of the cuBLAS library for BLAS routines on CUDA devices.
# If set to ON, cuBLAS will be used. If set to OFF (default), the library will not use cuBLAS
# even if it is available.
option(CYDL_CUBLAS "Cynthia-DL: use cuBLAS" OFF)

# CYDL_METAL: This option controls the usage of the Metal API on macOS for GPU computations.
# If set to ON, Metal will be used. If set to OFF (default), the library will not use Metal
# even if it available on the system.
option(CYDL_METAL "Cynthia-DL: use Metal" OFF)


########################################################
## Sanitizer Configuration Options:
########################################################

# The Sanitizers section is dedicated to enabling various sanitizers that help in detecting different
# kinds of bugs and issues in the code

# CYDL_SANITIZE_THREAD: This option enables thread sanitizer, a tool that detects data races.
# If this is ON, the -fsanitize=thread flag is appended to both C and C++ flags, enabling
# the thread sanitizer for the project.
if (CYDL_SANITIZE_THREAD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}     -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif ()

# CYDL_SANITIZE_ADDRESS: This option enables address sanitizer, a fast memory error detector.
# If this is ON, the -fsanitize=address -fno-omit-frame-pointer flags are appended to both C and C++ flags,
# enabling the address sanitizer for the project.
if (CYDL_SANITIZE_ADDRESS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}     -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif ()

# CYDL_SANITIZE_UNDEFINED: This option enables undefined behavior sanitizer, a tool that detects undefined behavior.
# If this is ON, the -fsanitize=undefined flag is appended to both C and C++ flags, enabling
# the undefined behavior sanitizer for the project.
if (CYDL_SANITIZE_UNDEFINED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}     -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif ()


option(CYDL_AVX                     "Cynthia-DL: enable AVX"                                     ON)
option(CYDL_AVX2                    "Cynthia-DL: enable AVX2"                                    ON)
option(CYDL_AVX512                  "Cynthia-DL: enable AVX512"                                  OFF)
option(CYDL_AVX512_VBMI             "Cynthia-DL: enable AVX512-VBMI"                             OFF)
option(CYDL_AVX512_VNNI             "Cynthia-DL: enable AVX512-VNNI"                             OFF)
option(CYDL_FMA                     "Cynthia-DL: enable FMA"                                     ON)
if (NOT MSVC)
    option(CYDL_F16C                "Cynthia-DL: enable F16C"                                    ON)
endif()




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
