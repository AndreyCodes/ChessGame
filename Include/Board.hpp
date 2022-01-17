#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
#include<optional>

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
public:
	Cell space[8][8];
	
	std::vector<Pawn> player_1;
	std::vector<Pawn> player_2;

private:
	sf::Sprite board_sprite;
	sf::Texture board_texture;

public:
	Board(RenderSystem& render);
	bool checkWinner();
	Cell& space_cell(sf::Vector2i);

	std::optional<std::reference_wrapper<Pawn>> getPlayer_1_PawnOnPosition(sf::Vector2i v);
	std::optional<std::reference_wrapper<Pawn>> getPlayer_2_PawnOnPosition(sf::Vector2i v);
	operator sf::Drawable& () override;
	void debug();
};