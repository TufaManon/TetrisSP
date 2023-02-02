cmake_minimum_required(VERSION 3.8)
project("Tetris" VERSION 0.1)

add_executable(Tetris "tetris.cc" scene/scene.cc loop-node.cc loop-node.h game-window.cc game-window.h
		scene/game-index.cc scene/game-index.h graphics.cc graphics.h tty.h texture.cc texture.h scene/the-game.cc
		scene/the-game.h scene/matrix.cc scene/matrix.h scene/tetris-actuator.cc scene/tetris-actuator.h scene/tetris-operator.cc scene/tetris-operator.h scene/generator.cc scene/generator.h font.cc font.h audio.cc audio.h)

include(cmake/sdl.cmake)

set_property(TARGET Tetris PROPERTY CXX_STANDARD 17) 

set(yaml-cpp_DIR "C:/Program Files (x86)/YAML_CPP/share/cmake/yaml-cpp")

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(Tetris PRIVATE SDLDep)
target_link_libraries(Tetris PRIVATE yaml-cpp)
target_link_libraries(Tetris PRIVATE nlohmann_json::nlohmann_json)

include_directories(Tetris INTERFACE "${PROJECT_SOURCE_DIR}")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory
				"${PROJECT_SOURCE_DIR}/assets"
				"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets"
				)
