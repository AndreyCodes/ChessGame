#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
#include"IRenderable.hpp"
#include"UI_helper.hpp"

struct RenderSystem
{
private:
	std::vector<IRenderable*> objs;
	std::vector<UI_helperCell> UI_helpers;
	IRenderable* board_sprite;
	sf::RenderWindow& window;
public:
	RenderSystem(sf::RenderWindow& ref);

	void setBoardTexture(IRenderable& board);

	void update();

	void add(IRenderable& some);

	
	void add_UI_helper(UI_helperCell some);
	void add_UI_helper(int x, int y, UI_helperCell::color c);//emplace construct
	void add_UI_helper(sf::Vector2i pos, UI_helperCell::color c);

	void remove_UI_helpers();

	void remove(IRenderable& some);
};