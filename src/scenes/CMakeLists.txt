target_sources(scenesLib
    PRIVATE
        Scene.cpp
        MainScene.cpp
        SceneSwitcher.cpp
        ActionObserver.cpp
)

target_include_directories(scenesLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
