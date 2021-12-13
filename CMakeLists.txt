cmake_minimum_required(VERSION 3.13)
project(nodes_frontend)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CXXFLAGS})
if(${DEBUG})
    add_definitions(-DDEBUG)
endif(${DEBUG})

if(${BENCHMARK})
    add_definitions(-DBENCHMARK)
endif(${BENCHMARK})

set(LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(SFML_PREFIX "D:/disk_backup/C++/libraries/SFML-2.5.1")
set(CMAKE_PREFIX_PATH ${SFML_PREFIX})
set(SFML_DIR ${CMAKE_PREFIX_PATH}/build)
set(SFML_INCLUDE_DIR ${SFML_PREFIX}/include)


find_package(SFML 2.5.1 COMPONENTS window system graphics REQUIRED)
find_package(OpenGL REQUIRED)


add_subdirectory(src)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/Inconsolata-Medium.ttf DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
