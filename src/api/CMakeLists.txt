target_sources(${apiLib}
    PRIVATE
        NodeFrontEndWrapper.cpp
        NodeFrontEnd.cpp
        Node.cpp
        LinkedListNode.cpp
)

target_include_directories(${apiLib} PUBLIC ${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${LOCAL_INCLUDE_DIR})
