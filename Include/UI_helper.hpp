#pragma once
#include<SFML/Graphics.hpp>
#include"IRenderable.hpp"


struct UI_helperCell : IRenderable
{
	sf::RectangleShape representation;
	sf::Texture texture;
	enum class color
	{
		green,
		red,
		yellow
	};

	UI_helperCell(int x, int y, color cl);
	operator sf::Drawable& () override;
};