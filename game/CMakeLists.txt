project("${CMAKE_PROJECT_NAME}-Game" VERSION ${CMAKE_PROJECT_VERSION}
        DESCRIPTION "..." LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC src/game.cc src/game.h
        src/ui/controller/ui-controller.cc src/ui/controller/ui-controller.h
        src/ui/ui.h
        src/ui/widget.h
        src/response/response.h
        src/request/request.h
        src/ui/index-ui/index-ui.cc src/ui/index-ui/index-ui.h
        src/ui/index-ui/selection-bar.cc src/ui/index-ui/selection-bar.h
        src/color/argb.cc src/color/argb.h
        src/sdl-error-handle.h
        src/resource-manager.cpp src/resource-manager.h
        src/ui/game-ui/standard-game-ui.cpp src/ui/game-ui/standard-game-ui.h
        src/ui/game-ui/matrix.cc src/ui/game-ui/matrix.h
        src/ui/simple-ui.cc src/ui/simple-ui.h src/sdl/texture.cc src/sdl/texture.h src/tetrimino/mino.cc
        src/tetrimino/mino.h src/tetrimino/tetrimino.h src/server/single-game-service.cc
        src/server/single-game-service.h src/tetrimino/seven-bag-generator.cc src/tetrimino/seven-bag-generator.h
        src/server/tetris-engine.cc src/server/tetris-engine.h src/utils/utils.cc src/utils/utils.h src/utils/point.cc
        src/utils/point.h src/server/srs.cc src/server/srs.h src/server/server.cc src/scene/matrix.cc src/scene/matrix.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set(yaml-cpp_DIR "C:/Program Files (x86)/YAML_CPP/share/cmake/yaml-cpp")

find_package(yaml-cpp CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC SDLDep)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)


target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

