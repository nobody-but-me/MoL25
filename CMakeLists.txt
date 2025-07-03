
cmake_minimum_required(VERSION 3.21)
project(MOL C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
	${CMAKE_SOURCE_DIR}/engine/src/include/
)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/engine/src/src/*.c)

add_executable(mol ${SRC_FILES})
target_compile_options(mol PRIVATE -Wall -Werror -pedantic)
target_link_libraries(mol PRIVATE glfw)


