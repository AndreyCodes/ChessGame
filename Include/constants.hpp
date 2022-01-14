#pragma once

namespace sizes
{
	constexpr inline int resolution = 1080;
	

	constexpr inline int board_texture_size = 1080;
	constexpr inline int width_of_outline_of_field = 36;

	inline sf::Vector2f width_of_outline_of_field_vec{ 36,36 };
	constexpr inline int size_of_game_field = 1008; //1080-36-36;
	constexpr inline int size_of_cell = 126;
	const static inline sf::Vector2f position_offset_texture_pawn{ 32,8 };
}