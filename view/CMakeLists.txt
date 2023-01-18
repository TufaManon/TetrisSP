project("${CMAKE_PROJECT_NAME}-View" VERSION ${CMAKE_PROJECT_VERSION}
        DESCRIPTION "the sdl gui lib used by game" LANGUAGES CXX)

unset(SRC_LIST)

list(APPEND SRC_LIST "src/view.cc" "src/view.h")

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} SDLDep)

target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")