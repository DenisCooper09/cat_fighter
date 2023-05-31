set(SOURCES
        main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-audio
        sfml-graphics
        sfml-network
        sfml-system
        sfml-window
        )
