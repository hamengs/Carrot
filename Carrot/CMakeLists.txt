add_library(Carrot SHARED
    src/Application.cpp
    src/Application.h
)

target_compile_features(Carrot PUBLIC cxx_std_17)
target_include_directories(Carrot PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_definitions(Carrot PRIVATE CARROT_BUILD_DLL)
