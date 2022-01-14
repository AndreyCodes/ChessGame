#include"../Include/UI_helper.hpp"
#include"../Include/constants.hpp"

UI_helperCell::UI_helperCell(int x, int y, color cl)
{
	sf::Texture tex;
	switch (cl)
	{
	case color::green:
	{
		tex.loadFromFile("gamedata/GreenCell.png");
		break;
	}
	case color::red:
	{
		tex.loadFromFile("gamedata/RedCell.png");
		break;
	}
	case color::yellow:
	{
		tex.loadFromFile("gamedata/YellowCell.png");
		break;
	}
	}
	texture.swap(tex);
	representation.setTexture(&texture);
	representation.setSize(sf::Vector2f(texture.getSize()));
	representation.setPosition(sf::Vector2f{ (float)x * sizes::size_of_cell, (float)y * sizes::size_of_cell } + sizes::width_of_outline_of_field_vec);

}
UI_helperCell::operator sf::Drawable& ()
{
	return representation;
}