project("${CMAKE_PROJECT_NAME}-Controller" VERSION ${CMAKE_PROJECT_VERSION}
		DESCRIPTION "controller" LANGUAGES CXX)

unset(SRC_LIST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

list(APPEND SRC_LIST "src/controller.cc" "src/controller.h" )

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} SDLDep)

target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}-View)

target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

