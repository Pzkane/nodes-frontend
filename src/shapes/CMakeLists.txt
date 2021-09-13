target_sources(shapesLib
    PRIVATE
        GL_Triangle.cpp
)

target_include_directories(shapesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
