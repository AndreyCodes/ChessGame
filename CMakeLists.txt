
cmake_minimum_required (VERSION 3.8)

project ("ChessGame")
set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable (ChessGame "ChessGame.cpp" "ChessGame.hpp" "Include/IRenderable.hpp" "Include/Pawn.hpp" "Include/RenderSystem.hpp" "Include/Board.hpp" "Include/MouseCoord.hpp" "Include/constants.hpp" "source/Board.cpp" "source/MouseCoord.cpp" "source/Pawn.cpp" "source/RenderSystem.cpp" "source/UI_helper.cpp" "Include/EndingSprite.hpp" "source/EndingSprite.cpp" "Include/AI_player.hpp" "source/AI_player.cpp" "source/Local_player.cpp")
target_link_libraries(ChessGame PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/gamedata DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

foreach(lib ${SFML_LIBS})
      get_target_property(lib_path ${lib} LOCATION)
      file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
