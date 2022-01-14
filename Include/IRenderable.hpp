#pragma once
struct IRenderable
{
	virtual operator sf::Drawable& () = 0;
};