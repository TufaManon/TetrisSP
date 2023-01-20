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
        src/color/argb.cc src/color/argb.h src/sdl-error-handle.h src/resource-manager.cpp src/resource-manager.h src/ui/game-ui/standard-game-ui.cpp src/ui/game-ui/standard-game-ui.h src/ui/game-ui/matrix.cc src/ui/game-ui/matrix.h)

target_link_libraries(${PROJECT_NAME} SDLDep)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

