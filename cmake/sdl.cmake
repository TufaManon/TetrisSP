#SDL dependences
set(SDL2_PATH "C:\\Program Files (x86)\\SDL2\\cmake")
set(SDL2_image_PATH "C:\\Program Files (x86)\\SDL2_image-2.6.2\\cmake")
set(SDL2_mixer_PATH "C:\\Program Files (x86)\\SDL2_mixer\\cmake")
set(SDL2_ttf_PATH "C:\\Program Files (x86)\\SDL2_ttf\\cmake")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

function(add_sdl_dependences t)
target_link_libraries(${t} PRIVATE  SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(${t} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${t} PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(${t} PRIVATE SDL2_ttf::SDL2_ttf)
endfunction()