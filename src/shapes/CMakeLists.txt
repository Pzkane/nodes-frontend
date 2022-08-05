target_sources(shapesLib
    PRIVATE
        AbstractShape.cpp
        GL_Triangle.cpp
        CircleShape.cpp
)

target_include_directories(shapesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
