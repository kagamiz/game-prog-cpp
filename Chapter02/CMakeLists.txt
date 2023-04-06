set(target Chapter02)

file(GLOB headers *.h)
file(GLOB cpps *.cpp)


add_executable(${target}
    ${headers}
    ${cpps}
)

target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/include
    ${CMAKE_SOURCE_DIR}/external/SDL_image
)

target_link_libraries(${target}
    ${CMAKE_SOURCE_DIR}/prebuilt/SDL/libSDL2-2.0.so
    ${CMAKE_SOURCE_DIR}/prebuilt/SDL_image/libSDL2_image.so
)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/${target})
