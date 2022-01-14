#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

#include"IRenderable.hpp"
#include"Pawn.hpp"
#include"RenderSystem.hpp"


struct Board : IRenderable
{
private:
	struct Cell
	{
		bool player_1 = 0;
		bool player_2 = 0;
	};
public://�������
	Cell space[8][8];
	//mb ���������
	std::vector<Pawn> player_1;
	std::vector<Pawn> player_2;


	sf::Sprite board_sprite;
	sf::Texture board_texture;

public:
	Board(RenderSystem& render);
	operator sf::Drawable& () override;
};