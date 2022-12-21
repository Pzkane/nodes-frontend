cmake_minimum_required(VERSION 3.13)
project(nodes_frontend)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CXXFLAGS})
if(${DEBUG})
    add_definitions(-DDEBUG)
endif(${DEBUG})

if(${BENCHMARK})
    add_definitions(-DBENCHMARK)
endif(${BENCHMARK})

file(READ ".env" env)
string(REGEX MATCH "SFML_PREFIX (.+)" _ ${env})

set(LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(SFML_PREFIX ${CMAKE_MATCH_1}) #"C:/Users/zuravpav/OneDrive - TietoEVRY/Documents/cxx/cxx_libs/sfml"
set(CMAKE_PREFIX_PATH ${SFML_PREFIX})
set(LOCAL_BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/build)
set(SFML_INCLUDE_DIR ${SFML_PREFIX}/include)
set(SFML_BIN_DIR ${SFML_PREFIX}/bin)
set(EXECUTABLE_NAME ${PROJECT_NAME}_bin)


find_package(SFML 2.5.1 COMPONENTS window system graphics REQUIRED)
find_package(OpenGL REQUIRED)


add_subdirectory(src)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if(${EXAMPLE})
    # install program
    install(FILES ${LOCAL_BUILD_DIR}/src/${EXECUTABLE_NAME}.exe DESTINATION ${SFML_BIN_DIR})
    # install fonts
    install(FILES ${CMAKE_SOURCE_DIR}/resources/Inconsolata-Medium.ttf DESTINATION ${SFML_BIN_DIR}/resources)
    # install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/Inconsolata-Medium.ttf DESTINATION ${SFML_BIN_DIR})
endif(${EXAMPLE})
