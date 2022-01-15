#include "ChessGame.hpp"


int main()
{

	sf::RenderWindow window(sf::VideoMode(1080, 1080), "ChessGame");
	RenderSystem render(window);

	Board b{ render };

	enum state
	{
		pl1_choosing_pawn,
		pl1_choosing_way,
		pl2_choosing_pawn,
		pl2_choosing_way,
		finish,
	};
	state current_state = state::pl1_choosing_pawn;

	struct player
	{
		sf::Vector2i choosed_pawn;
		std::vector<sf::Vector2i> available_ways;//Ходы, куда может игрок пойти
	}player1;


	struct ai
	{

	};



	while (window.isOpen())
	{
		sf::Event ev;
		MouseCoord cursor(window);

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			switch (current_state)
			{
			case state::pl1_choosing_pawn:
			{
				if (ev.type == sf::Event::EventType::MouseButtonPressed)
				{
					if (ev.mouseButton.button == sf::Mouse::Button::Left)
					{
						if (b.space[cursor.field_coord_clamp.x][cursor.field_coord_clamp.y].player_1 == 1)//==1 излишне, но для читаемости
						{
							for (int i = 0; i < b.player_1.size(); ++i)
							{
								if (b.player_1[i].x == cursor.field_coord_clamp.x && b.player_1[i].y == cursor.field_coord_clamp.y)
								{
									render.add_UI_helper(UI_helperCell(cursor.field_coord_clamp.x, cursor.field_coord_clamp.y, UI_helperCell::color::yellow));//Создаем подсказку, какую пешку выбрал игрок
									player1.choosed_pawn.x = cursor.field_coord_clamp.x;
									player1.choosed_pawn.y = cursor.field_coord_clamp.y;


									//test available ways
									auto test = [&b, &player1]
									{
										int x = player1.choosed_pawn.x;
										int y = player1.choosed_pawn.y;
										//можно ли ходить на право
										if (x + 1 <= 7)
										{
											//можно ли поставить пешку справа
											if (b.space[x + 1][y].player_1 != 1)
											{
												player1.available_ways.push_back({ x + 1,y });
											}
										}
										//можнно ли ходить на лево
										if (x - 1 >= 0)
										{
											if (b.space[x - 1][y].player_1 != 1)
											{
												player1.available_ways.push_back({ x - 1,y });
											}
										}
										//можно ли ходить на верх
										if (y + 1 <= 7)
										{
											if (b.space[x][y + 1].player_1 != 1)
											{
												player1.available_ways.push_back({ x,y + 1 });
											}
										}
										//можно ли ходить вниз
										if (y - 1 >= 0)
										{
											if (b.space[x][y - 1].player_1 != 1)
											{
												player1.available_ways.push_back({ x,y - 1 });
											}
										}
									}; test();//Проверяем.

									for (auto& el : player1.available_ways)
									{
										render.add_UI_helper(UI_helperCell(el.x, el.y, UI_helperCell::color::green));
									}
									current_state = state::pl1_choosing_way;

									break;
								}
							}
						}
					}
				}
				break;
			}
			case state::pl1_choosing_way:
			{
				if (ev.type == sf::Event::EventType::MouseButtonPressed)
				{
					if (ev.mouseButton.button == sf::Mouse::Button::Left)
					{
						if (player1.choosed_pawn.x == cursor.field_coord.x and player1.choosed_pawn.y == cursor.field_coord.y)
						{
							render.remove_UI_helpers();
							player1.available_ways.clear();
							current_state = state::pl1_choosing_pawn;
							break;
						}

						for (int i = 0; i < player1.available_ways.size(); ++i)
						{
							if (cursor.field_coord_clamp.x == player1.available_ways[i].x and cursor.field_coord_clamp.y == player1.available_ways[i].y)
							{
								for (auto& el : b.player_2)
								{
									if (el.x == player1.choosed_pawn.x && el.y == player1.choosed_pawn.y)
									{
										el.setPosition_as_default();
										break;
									}
								}

								b.space[player1.choosed_pawn.x][player1.choosed_pawn.y].player_1 = 0;
								b.space[cursor.field_coord_clamp.x][cursor.field_coord_clamp.y].player_1 = 1;
								for (auto& el : b.player_1)
								{
									if (el.x == player1.choosed_pawn.x and el.y == player1.choosed_pawn.y)
									{
										
										el.setPosition(cursor.field_coord_clamp.x, cursor.field_coord_clamp.y);
										for (auto& el_2 : b.player_2)
										{
											if (el_2.x == el.x and el_2.y == el.y)
											{
												el.setPosition_as_white();
												el_2.setPosition_as_black();
												break;
											}
										}
										break;
									}
								}

								break;
							}
						}
						render.remove_UI_helpers();
						player1.available_ways.clear();
						if (b.checkWinner())
						{
							current_state = state::finish;
						}
						else
						{
							current_state = state::pl1_choosing_pawn;//CHANGE!
						}
						break;


					}
				}

			}

			}




		}

		//std::cout << cursor.raw.x << ' ' << cursor.raw.y << '\n';

		render.update();


	}
}
