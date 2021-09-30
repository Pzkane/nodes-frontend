target_sources(mainLib
    PRIVATE
        main.cpp
)

add_executable(${PROJECT_NAME} main.cpp)


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

target_link_libraries(shapesLib sfml-graphics propertiesLib)
target_link_libraries(entitiesLib shapesLib)
target_link_libraries(${PROJECT_NAME}
    mainLib
    scenesLib
    shapesLib
    helpersLib
    entitiesLib
    propertiesLib
)
