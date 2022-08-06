target_sources(helpersLib
    PRIVATE
        utils.cpp
        FontFlags.cpp
        LoopFlags.cpp
)

target_include_directories(helpersLib PUBLIC ${LOCAL_INCLUDE_DIR})
