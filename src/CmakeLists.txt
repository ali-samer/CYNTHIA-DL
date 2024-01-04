add_library(cydl demo.cpp)
target_include_directories(cydl PUBLIC
                            ${PROJECT_SOURCE_DIR}/include)

target_compile_features(cydl PUBLIC cxx_std_23)