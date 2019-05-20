cmake_minimum_required(VERSION 3.13.3)
PROJECT(3DPlatformer)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/irrlicht")
include_directories("${PROJECT_SOURCE_DIR}/lib/irrlicht/include")

FILE(GLOB SRCS src/*.cpp)

ADD_EXECUTABLE(3DPlatformer
   ${SRCS}
)
