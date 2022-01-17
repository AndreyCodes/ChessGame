#include"../Include/Local_player.hpp"

bool local_player::HasAvailableWayWithCoord(sf::Vector2i v)
{
	for (int i = 0; i < available_ways.size(); ++i)
	{
		if (v == available_ways[i])
		{
			return true;
		}
	}
	return false;
}


void local_player::FindAvailableWaysForChoosedPawn(Board& b)
{
	int x = choosed_pawn.x;
	int y = choosed_pawn.y;
	//можно ли ходить на право
	if (x + 1 <= 7)
	{
		//можно ли поставить пешку справа
		if (b.space[x + 1][y].player_1 != 1)
		{
			available_ways.push_back({ x + 1,y });
		}
	}
	//можнно ли ходить на лево
	if (x - 1 >= 0)
	{
		if (b.space[x - 1][y].player_1 != 1)
		{
			available_ways.push_back({ x - 1,y });
		}
	}
	//можно ли ходить на верх
	if (y + 1 <= 7)
	{
		if (b.space[x][y + 1].player_1 != 1)
		{
			available_ways.push_back({ x,y + 1 });
		}
	}
	//можно ли ходить вниз
	if (y - 1 >= 0)
	{
		if (b.space[x][y - 1].player_1 != 1)
		{
			available_ways.push_back({ x,y - 1 });
		}
	}

}