# CMakeList.txt: TetrisSP 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("TetrisSP")
add_subdirectory("game")

# 将源代码添加到此项目的可执行文件。
add_executable (TetrisSP "TetrisSP.cpp" "TetrisSP.h")
target_link_libraries(TetrisSP PRIVATE game)

include("cmake/sdl.cmake")

add_sdl_dependences(TetrisSP)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TetrisSP PROPERTY CXX_STANDARD 20)
endif()

# copy the resources
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${PROJECT_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets"
)
# TODO: 如有需要，请添加测试并安装目标。
