
cmake_minimum_required (VERSION 3.8)

project ("ChessGame")
set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable (ChessGame "ChessGame.cpp" "ChessGame.hpp")
target_link_libraries(ChessGame PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/gamedata DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
