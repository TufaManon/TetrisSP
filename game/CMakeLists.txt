project("${CMAKE_PROJECT_NAME}-Game" VERSION ${CMAKE_PROJECT_VERSION}
		DESCRIPTION "..." LANGUAGES CXX)

 unset(SRC_LIST)

 list(APPEND SRC_LIST "src/game.cc" "src/game.h")

 add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

 target_link_libraries(${PROJECT_NAME} SDLDep)

 target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}-Controller)

 target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
