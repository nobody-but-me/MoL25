
cmake_minimum_required(VERSION 3.21)
project(MOL CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
	${CMAKE_SOURCE_DIR}/engine/src/include/
	${CMAKE_SOURCE_DIR}/engine/libs/glm/
	${CMAKE_SOURCE_DIR}/engine/libs/
)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/engine/src/include/MOL/*.cpp
	${CMAKE_SOURCE_DIR}/engine/src/src/*.cpp
)
find_package(glm CONFIG REQUIRED)

add_executable(mol ${SRC_FILES} ${CMAKE_SOURCE_DIR}/engine/libs/glad.c)
target_compile_options(mol PRIVATE -Wall -Werror -Wno-pointer-arith)
target_link_libraries(mol PRIVATE glfw glm::glm)


