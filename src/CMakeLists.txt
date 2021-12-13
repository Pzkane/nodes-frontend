set(EXECUTABLE_NAME ${PROJECT_NAME}_bin)

add_library(merged INTERFACE)

target_include_directories(merged INTERFACE ${OPENGL_INCLUDE_DIRS} ${LOCAL_INCLUDE_DIR})
target_link_libraries(merged INTERFACE sfml-window sfml-system sfml-graphics ${OPENGL_LIBRARIES})
# target_include_directories(${PROJECT_NAME} PUBLIC ${LOCAL_INCLUDE_DIR})

if(${EXAMPLE})
    add_executable(${EXECUTABLE_NAME} main.cpp)
endif(${EXAMPLE})

set(apiLib ${PROJECT_NAME})
add_library(${apiLib})
add_subdirectory(api)

add_library(helpersLib)
add_subdirectory(helpers)

add_library(propertiesLib)
add_subdirectory(properties)

add_library(shapesLib)
add_subdirectory(shapes)

add_library(entitiesLib)
add_subdirectory(entities)

add_library(scenesLib)
add_subdirectory(scenes)

target_link_libraries(helpersLib sfml-graphics)
target_link_libraries(shapesLib sfml-graphics propertiesLib)
target_link_libraries(entitiesLib shapesLib)
target_link_libraries(${apiLib} sfml-window sfml-system sfml-graphics ${OPENGL_LIBRARIES}
    scenesLib
    shapesLib
    helpersLib
    entitiesLib
    propertiesLib
)
target_link_libraries(merged INTERFACE ${apiLib})
if(${EXAMPLE})
    target_link_libraries(${EXECUTABLE_NAME}
        ${apiLib}
    )
    # INSTALL
    install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${SFML_PREFIX}/bin)
    install(FILES ${CMAKE_SOURCE_DIR}/resources/Inconsolata-Medium.ttf DESTINATION ${SFML_PREFIX}/bin/resources)
endif()
