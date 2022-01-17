#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
#include"Board.hpp"

struct local_player
{
	sf::Vector2i choosed_pawn;
	std::vector<sf::Vector2i> available_ways;//Ходы, куда может игрок пойти
	bool HasAvailableWayWithCoord(sf::Vector2i v);

	void FindAvailableWaysForChoosedPawn(Board& b);
};