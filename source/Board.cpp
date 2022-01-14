#include"../Include/Board.hpp"

Board::Board(RenderSystem& render)
{
	sf::Texture t; t.loadFromFile("gamedata/Board.png");
	board_texture.swap(t);
	board_sprite.setTexture(board_texture);
	render.setBoardTexture(*this);


	player_1.reserve(8);
	player_2.reserve(8);
	for (int i = 5; i <= 7; ++i)
	{
		for (int j = 5; j <= 7; ++j)
		{
			player_1.push_back(Pawn(i, j, Pawn::owner_tag::player_1));
			space[i][j].player_1 = 1;
		}
	}
	for (int i = 0; i <= 2; ++i)
	{
		for (int j = 0; j <= 2; ++j)
		{
			player_2.push_back(Pawn(i, j, Pawn::owner_tag::player_2));
			space[i][j].player_2 = 1;
		}
	}
	for (int i = 0; i < player_1.size(); ++i)
	{
		render.add(player_1[i]);
		render.add(player_2[i]);
	}
	//todo->

}

Board::operator sf::Drawable& ()
{
	return board_sprite;
}

