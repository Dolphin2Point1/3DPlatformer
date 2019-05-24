cmake_minimum_required(VERSION 3.13.3)
PROJECT(3DPlatformer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

FILE(GLOB SRCS src/*)

ADD_EXECUTABLE(3DPlatformer ${SRCS})

option(USE_SYSTEM_IRRLICHT "Use system Irrlicht?" ON)
option(USE_SYSTEM_BULLET "Use system Bullet?" OFF)

if(USE_SYSTEM_IRRLICHT)
	find_package(Irrlicht)
	include_directories(${IRRLICHT_INCLUDE_DIR})
	target_link_libraries(3DPlatformer ${IRRLICHT_LIBRARY})
else()
	add_subdirectory("${PROJECT_SOURCE_DIR}/lib/irrlicht")
	include_directories("${PROJECT_SOURCE_DIR}/lib/irrlicht/include")
	target_link_libraries(3DPlatformer irrlicht)
endif()

if(USE_SYSTEM_BULLET)
	find_package(Bullet)
	include_directories(${BULLET_INCLUDE_DIR})
	target_link_libraries(3DPlatformer general ${BULLET_LIBRARIES})
else()
	add_subdirectory("${PROJECT_SOURCE_DIR}/lib/bullet")
	include_directories("${PROJECT_SOURCE_DIR}lib/bullet/src")
	target_link_libraries(3DPlatformer general BULLET_PHYSICS)
endif()
