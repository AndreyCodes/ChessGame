#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
#include"IRenderable.hpp"

struct RenderSystem
{
protected:
	std::vector<IRenderable*> objs;
	std::vector<IRenderable*> UI_helpers;
	IRenderable* board_sprite;
	sf::RenderWindow& window;
public:
	RenderSystem(sf::RenderWindow& ref);

	void setBoardTexture(IRenderable& board);

	void update();

	void add(IRenderable& some);

	void add_UI_helper(IRenderable& some);

	void remove_UI_helpers();

	void remove(IRenderable& some);
};