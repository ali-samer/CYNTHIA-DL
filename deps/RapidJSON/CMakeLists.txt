include(FetchContent)
FetchContent_Declare(
        rapidJSON
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG        master
)
set(BUILD_DOC OFF CACHE BOOL "Disable doc" FORCE)
FetchContent_MakeAvailable(rapidJSON)
