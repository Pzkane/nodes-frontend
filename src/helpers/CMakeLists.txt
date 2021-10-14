target_sources(helpersLib
    PRIVATE
        utils.cpp
        Flags.cpp
        LoopFlags.cpp
)

target_include_directories(helpersLib PUBLIC ${LOCAL_INCLUDE_DIR})
