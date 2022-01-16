#include<SFML/Graphics.hpp>
#include"IRenderable.hpp"

struct EndingSprite : IRenderable
{
	sf::Sprite sprite;
	sf::Texture texture;
	enum class type
	{
		lost,
		win
	};
	EndingSprite(type t);
	operator sf::Drawable& () override;
};