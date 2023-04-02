set(target Chapter01)

add_executable(${target}
    Game.cpp
    Main.cpp
)

target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/include
)

target_link_libraries(${target}
    SDL2
)
