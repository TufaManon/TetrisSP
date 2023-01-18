find_package(SDL2 CONFIG REQUIRED)

find_package(SDL2_ttf CONFIG REQUIRED)

find_package(SDL2_mixer CONFIG REQUIRED)

find_package(SDL2_image CONFIG REQUIRED)

add_library(SDLDep INTERFACE)

target_link_libraries(SDLDep INTERFACE ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)