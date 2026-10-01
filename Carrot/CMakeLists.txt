add_library(Carrot SHARED
    src/Application.cpp
    src/Application.h
    src/Log.cpp
    src/Log.h

    src/Events/Events.cpp
    src/Events/Event.h
    src/Events/ApplicationEvent.h
    src/Events/KeyEvent.h
    src/Events/MouseEvent.h
)

target_compile_features(Carrot PUBLIC cxx_std_17)
target_include_directories(Carrot PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_definitions(Carrot PRIVATE CARROT_BUILD_DLL)
target_link_libraries(Carrot PUBLIC spdlog::spdlog)
