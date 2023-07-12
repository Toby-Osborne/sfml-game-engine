cmake_minimum_required(VERSION 3.25)
project(cppgame_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppgame_test src/main.cpp src/Engine.cpp src/TileMap.cpp include/TileMap.h)

set(SFML_STATIC ON)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

set(SFML_ROOT F:/Programming/CPP/toolchains/SFML-Downloaded)

set(MINGW64_BIN_DIR C:/msys64/mingw64/bin)

set(SFML_BIN_DIR ${SFML_ROOT}/bin)

set(SFML_INCLUDE_DIR ${SFML_ROOT}/include)

set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

include_directories(SFML_INCLUDE_DIR ./include)

# At some point need to make this build from local toolchain so can compile on linux
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cppgame_test sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_BIN_DIR}/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
#    file(GLOB MINGW_DEP_DLLS "${MINGW64_BIN_DIR}/*.dll")
#    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

