include(FetchContent)
FetchContent_Declare(
        eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG        3.4.0
)
set(BUILD_DOC OFF CACHE BOOL "Disable doc" FORCE)
FetchContent_MakeAvailable(eigen)
