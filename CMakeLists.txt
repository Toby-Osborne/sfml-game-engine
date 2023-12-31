cmake_minimum_required(VERSION 3.25)
project(cppgame_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppgame_test src/main.cpp src/Engine.cpp src/ChunkHandler.cpp src/Map.cpp include/Map.h src/Player.cpp include/Player.h src/Chunk.cpp include/Chunk.h include/EngineDefines.h)

#set(SFML_ROOT F:/Programming/CPP/toolchains/SFML-Downloaded)

include_directories(SFML_INCLUDE_DIR ./include)

# At some point need to make this build from local toolchain so can compile on linux
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cppgame_test sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/saves)

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_BIN_DIR}/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "${MINGW64_BIN_DIR}/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()

