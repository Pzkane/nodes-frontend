target_sources(actionsLib
    PRIVATE
        ActionObserver.cpp
        ActionObservable.cpp
)

target_include_directories(actionsLib PUBLIC ${SFML_INCLUDE_DIR} ${LOCAL_INCLUDE_DIR})
