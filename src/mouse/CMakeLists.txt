target_sources(mouseLib
    PRIVATE
        MouseCache.cpp
)

target_include_directories(mouseLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
