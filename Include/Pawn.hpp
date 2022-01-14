#pragma once
#include<SFML/Graphics.hpp>
#include"IRenderable.hpp"

struct Pawn : IRenderable
{

	enum class owner_tag
	{
		player_1,
		player_2
	};

	int x, y;
	owner_tag owner;
	sf::RectangleShape representation;
	Pawn(int x_, int y_, owner_tag ow);

private:
	void setPosition(sf::Vector2f v);//set only view position;

public:
	void setPosition(int x_, int y_); // set view and logic position

	operator sf::Drawable& () override;

	const static inline sf::Vector2f position_offset{ 32,8 };
	const static inline sf::Texture default_white = [] {sf::Texture t; t.loadFromFile("gamedata/whitePawn.png"); return t; }();
	const static inline sf::Texture default_black = [] {sf::Texture t; t.loadFromFile("gamedata/blackPawn.png"); return t; }();
};