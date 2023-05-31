set(SOURCES
        main.cpp
        tile_map.cpp
        tile_map.h
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-audio
        sfml-graphics
        sfml-network
        sfml-system
        sfml-window
        )
