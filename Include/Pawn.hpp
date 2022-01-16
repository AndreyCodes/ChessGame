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

	sf::Vector2i position;
	owner_tag owner;
	Pawn(int x_, int y_, owner_tag ow);

private:
	sf::RectangleShape representation;
	void setPosition(sf::Vector2f v);//set only view position;

public:
	void setPosition(sf::Vector2i pos); // set view and logic position

	void setPosition_as_white();
	void setPosition_as_black();
	void setPosition_as_default();

	operator sf::Drawable& () override;

private:
	const static inline sf::Vector2f position_offset{ 32,8 };
	const static inline sf::Vector2f position_offset_black{ -10,0 };
	const static inline sf::Vector2f position_offset_white{ 10,0 };
	const static inline sf::Texture default_white = [] {sf::Texture t; t.loadFromFile("gamedata/whitePawn.png"); return t; }();//produce some issue with sfml implementation of OpenGL
	const static inline sf::Texture default_black = [] {sf::Texture t; t.loadFromFile("gamedata/blackPawn.png"); return t; }();
};