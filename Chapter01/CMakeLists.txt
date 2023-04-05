set(target Chapter01)

file(GLOB headers *.h)
file(GLOB cpps *.cpp)


add_executable(${target}
    ${headers}
    ${cpps}
)

target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/include
)

target_link_libraries(${target}
    SDL2
)
