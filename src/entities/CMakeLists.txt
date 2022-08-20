target_sources(entitiesLib
    PRIVATE
        Entity.cpp
        Connector.cpp
        _Node.cpp
        Node.cpp
)

target_include_directories(entitiesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
