#include<random>

#include"../Include/AI_player.hpp"

ai_player::ai_player(Board& ref_) : ref{ ref_ } {}

void ai_player::choosePawn()
{
	if (available_ways.size() != 9)
	{
		available_ways.reserve(9);
		for (auto& p : ref.player_2)
		{
			available_ways.push_back({ &p,{} });
		}
	}

	auto test = [this](std::pair<Pawn*, std::vector<sf::Vector2i>>& p)
	{

		int x = p.first->position.x;
		int y = p.first->position.y;
		//����� �� ������ �� �����
		if (x + 1 <= 7)
		{
			//����� �� ��������� ����� ������
			if (ref.space[x + 1][y].player_2 != 1)
			{
				p.second.push_back({ x + 1,y });
			}
		}
		//������ �� ������ �� ����
		if (x - 1 >= 0)
		{
			if (ref.space[x - 1][y].player_2 != 1)
			{
				p.second.push_back({ x - 1,y });
			}
		}
		//����� �� ������ �� ����
		if (y + 1 <= 7)
		{
			if (ref.space[x][y + 1].player_2 != 1)
			{
				p.second.push_back({ x,y + 1 });
			}
		}
		//����� �� ������ ����
		if (y - 1 >= 0)
		{
			if (ref.space[x][y - 1].player_2 != 1)
			{
				p.second.push_back({ x,y - 1 });
			}
		}
	};

	for (auto& el : available_ways)
	{
		el.second.clear();
	}//
	std::for_each(available_ways.begin(), available_ways.end(), test);

	auto select_pawn = [this]
	{

		for (auto& el : available_ways)
		{
			for (auto& way : el.second)
			{
				for (int i = 0; i < 8; ++i)
				{
					for (int j = 0; j < 8; ++j)
					{
						if (ref.space[i][j].player_1 == 1 and way.x == i and way.y == j)//��� ����������
						{
							return &el;
						}
					}
				}
			}
		}
		//else
		std::random_device rd;
		while (true)
		{
			auto pawn_id = rd() % 9;
			if (!available_ways[pawn_id].second.empty())
			{
				return &available_ways[pawn_id];
			}

		}

	};

	choosed_pawn = select_pawn();

}