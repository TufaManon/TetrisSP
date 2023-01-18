# CMakeList.txt: TetrisSP 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("TetrisSP" VERSION 0.1)

list(APPEND SRC_LIST "src/TetrisSP.cpp" "src/TetrisSP.h")

# 将源代码添加到此项目的可执行文件。
add_executable (TetrisSP ${SRC_LIST})

# 设置c++标准
set_property(TARGET TetrisSP PROPERTY CXX_STANDARD 17)

add_subdirectory(view)

add_subdirectory(controller)

add_subdirectory(game)

include(cmake/sdl.cmake)

target_link_libraries(TetrisSP TetrisSP-Game)

# copy the resources
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${PROJECT_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets"
)
# TODO: 如有需要，请添加测试并安装目标。
