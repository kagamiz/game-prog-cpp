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
    ${CMAKE_SOURCE_DIR}/prebuilt/SDL/libSDL2-2.0.so
)
