cmake_minimum_required(VERSION 3.8)
set(EXECUTABLE_NAME veteris)
project(${EXECUTABLE_NAME})

set(CMAKE_CXX_STANDARD 17)
include_directories(src include)

set(SOURCE_FILES main.cpp include/geom/Matrix.h include/geom/Point.h include/geom/Vector.h include/geom/Normal.h include/geom/Transform.h include/geom/Box.h include/geom/Mesh.h)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Add boost
find_package(Boost 1.34.0 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()
