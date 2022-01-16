#include<algorithm>
#include"../Include/MouseCoord.hpp"
#include"../Include/constants.hpp"

MouseCoord::MouseCoord(sf::RenderWindow& ref)
{
	raw = sf::Mouse::getPosition(ref);
	field_coord = (raw - offset) / sizes::size_of_cell;
	discrete = field_coord * sizes::size_of_cell;
	field_coord_clamp = [this]
	{
		sf::Vector2i cl = raw - offset;
		cl.x = std::clamp(cl.x, 0, sizes::size_of_game_field - 1) / sizes::size_of_cell;
		cl.y = std::clamp(cl.y, 0, sizes::size_of_game_field - 1) / sizes::size_of_cell;
		return cl;
	}();

}