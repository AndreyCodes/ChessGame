#pragma once
#include<SFML/Graphics.hpp>

struct MouseCoord
{
	const static inline sf::Vector2i offset{ 36,36 };// == width of outline

	sf::Vector2i raw;
	sf::Vector2i discrete;
	sf::Vector2i field_coord;
	sf::Vector2i field_coord_clamp;
	MouseCoord(sf::RenderWindow& ref);
};