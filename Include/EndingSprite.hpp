#pragma once
#include<SFML/Graphics.hpp>
#include"IRenderable.hpp"

struct EndingSprite : IRenderable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	enum class type
	{
		lost,
		win
	};
	EndingSprite(type t);
	operator sf::Drawable& () override;
};