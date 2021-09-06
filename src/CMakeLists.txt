target_sources(mainLib
    PRIVATE
        main.cpp
)

add_executable(${PROJECT_NAME} main.cpp)


add_library(helpersLib)
add_subdirectory(helpers)


target_link_libraries(${PROJECT_NAME} mainLib helpersLib)
