project(TetrisSP_game LANGUAGES CXX)
list(APPEND MODEL_SRC "model/iModel.hpp" "model/homeModel.hpp" "model/soloModel.hpp")
add_library(game STATIC "game.cpp" "game.h" "controller/controller.hpp" "animation/animation.hpp" "color/color.hpp" "types/types.hpp" ${MODEL_SRC} "model/model.cpp")
set(yaml-cpp_DIR "C:\\Program Files (x86)\\YAML_CPP\\share\\cmake\\yaml-cpp")
find_package(yaml-cpp CONFIG REQUIRED)

target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
include("../cmake/sdl.cmake")
add_sdl_dependences(game)

target_link_libraries(game PUBLIC yaml-cpp)