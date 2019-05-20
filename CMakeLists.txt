cmake_minimum_required(VERSION 3.13.3)
PROJECT(3DPlatformer)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/irrlicht")
include_directories("${PROJECT_SOURCE_DIR}/lib/irrlicht/include")

target_link_libraries(3DPirrlicht)

FILE(GLOB SRCS src/*)

ADD_EXECUTABLE(3DPlatformer ${SRCS})
