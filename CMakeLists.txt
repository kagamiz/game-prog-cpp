cmake_minimum_required(VERSION 3.23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(game-prog-cpp)

include(ProcessorCount)
ProcessorCount(N)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/tmp/make-prebuilt-libs/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/make-prebuilt-libs)
if(result)
    message(FATAL_ERROR "CMake step for SDL failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build . -j${N}
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/make-prebuilt-libs)
if(result)
    message(FATAL_ERROR "Build step for SDL failed: ${result}")
endif()

add_subdirectory(Chapter01)
add_subdirectory(Chapter02)
