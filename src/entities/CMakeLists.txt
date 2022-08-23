target_sources(entitiesLib
    PRIVATE
        Edge.cpp
        WeightedEdge.cpp
        _Node.cpp
)

target_include_directories(entitiesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
