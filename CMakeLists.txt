cmake_minimum_required(VERSION 3.13.3)
PROJECT(3DPlatformer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

FILE(GLOB SRCS src/*)

ADD_EXECUTABLE(3DPlatformer ${SRCS})

find_package(Irrlicht)
include_directories(${IRRLICHT_INCLUDE_DIR})
target_link_libraries(3DPlatformer ${IRRLICHT_LIBRARY})