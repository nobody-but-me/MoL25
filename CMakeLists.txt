
cmake_minimum_required(VERSION 3.21)
project(MOL CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
	${CMAKE_SOURCE_DIR}/engine/src/include/
	${CMAKE_SOURCE_DIR}/engine/libs/
)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/engine/src/include/MOL/*.cpp
	${CMAKE_SOURCE_DIR}/engine/src/src/*.cpp
	${CMAKE_SOURCE_DIR}/engine/libs/*.cpp
	${CMAKE_SOURCE_DIR}/engine/libs/*.c
)

add_executable(mol ${SRC_FILES})
target_compile_options(mol PRIVATE -Wall -Werror)
target_link_libraries(mol PRIVATE glfw)


