target_sources(entitiesLib
    PRIVATE
        Connector.cpp
        Node.cpp
)

target_include_directories(entitiesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
