cmake_minimum_required(VERSION 3.13)
project(tree_visualizer)

set(LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(SFML_PREFIX "D:/disk_backup/C++/libraries/SFML-2.5.1")
set(CMAKE_PREFIX_PATH ${SFML_PREFIX})
set(SFML_DIR ${CMAKE_PREFIX_PATH}/build)
set(SFML_INCLUDE_DIR ${SFML_PREFIX}/include)


find_package(SFML 2.5.1 COMPONENTS window system graphics REQUIRED)
find_package(OpenGL REQUIRED)


add_library(mainLib)
add_subdirectory(src)
target_include_directories(mainLib PUBLIC ${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${LOCAL_INCLUDE_DIR})


target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS} ${LOCAL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-system sfml-graphics ${OPENGL_LIBRARIES})


# INSTALL
install(TARGETS ${PROJECT_NAME} DESTINATION ${SFML_PREFIX}/bin)
