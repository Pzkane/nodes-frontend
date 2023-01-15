target_sources(entitiesLib
    PRIVATE
        Edge.cpp
        OrientedEdge.cpp
        WeightedEdge.cpp
        _Node.cpp
        Label.cpp
        Container.cpp
)

target_include_directories(entitiesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
