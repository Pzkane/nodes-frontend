target_sources(shapesLib
    PRIVATE
        AbstractShape.cpp
        CircleShape.cpp
        Line.cpp
)

target_include_directories(shapesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
