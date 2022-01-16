#include"../Include/Pawn.hpp"
#include"../Include/constants.hpp"

Pawn::Pawn(int x_, int y_, owner_tag ow) : position{x_,y_}, owner{ow}
{
	if (owner == owner_tag::player_1)
	{
		representation.setTexture(&default_white);
		representation.setSize(sf::Vector2f(default_white.getSize()));
	}
	if (owner == owner_tag::player_2)
	{
		representation.setTexture(&default_black);
		representation.setSize(sf::Vector2f(default_black.getSize()));
	}
	setPosition(position);
}

void Pawn::setPosition(sf::Vector2f v)//set only view position
{
	representation.setPosition(v + position_offset + sizes::width_of_outline_of_field_vec);
}

void Pawn::setPosition(sf::Vector2i pos) // set view and logic position
{
	position = pos;
	setPosition(sf::Vector2f(pos) * (float)sizes::size_of_cell);
}

void Pawn::setPosition_as_white()
{
	representation.move(position_offset_white);
}

void Pawn::setPosition_as_black()
{
	representation.move(position_offset_black);
}

void Pawn::setPosition_as_default()
{
	setPosition(position);
}

Pawn::operator sf::Drawable& ()
{
	return representation;
}