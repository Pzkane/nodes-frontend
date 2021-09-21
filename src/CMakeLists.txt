target_sources(mainLib
    PRIVATE
        main.cpp
)

add_executable(${PROJECT_NAME} main.cpp)


add_library(helpersLib)
add_subdirectory(helpers)

add_library(scenesLib)
add_subdirectory(scenes)

add_library(shapesLib)
add_subdirectory(shapes)

target_link_libraries(scenesLib helpersLib)
target_link_libraries(${PROJECT_NAME}
    mainLib
    helpersLib
    scenesLib
    shapesLib
)
