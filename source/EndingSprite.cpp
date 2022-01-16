#include"../Include/EndingSprite.hpp"

EndingSprite::EndingSprite(type t)
{
	switch (t)
	{
	case type::win:
	{
		texture.loadFromFile("gamedata/YouWin.png");
		break;
	}
	case type::lost:
		texture.loadFromFile("gamedata/YouLost.png");
		break;
	}
	sprite.setTexture(texture);
}
EndingSprite::operator sf::Drawable& ()
{
	return sprite;
}