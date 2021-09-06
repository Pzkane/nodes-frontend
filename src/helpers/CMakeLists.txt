target_sources(helpersLib
    PRIVATE
        LoopFlags.cpp
)

target_include_directories(helpersLib PUBLIC ${LOCAL_INCLUDE_DIR})
