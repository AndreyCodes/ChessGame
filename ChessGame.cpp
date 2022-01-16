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
		win_pl1,
		win_pl2,
		end,
	};
	state current_state = state::pl1_choosing_pawn;
	//state current_state = state::pl2_choosing_pawn;

	struct player
	{
		sf::Vector2i choosed_pawn;
		std::vector<sf::Vector2i> available_ways;//Ходы, куда может игрок пойти
	}player1;


	struct ai_player
	{
		ai_player(Board& ref_): ref{ref_}{}
		std::pair<Pawn*, std::vector<sf::Vector2i>>* choosed_pawn;
		std::vector < std::pair<Pawn*, std::vector<sf::Vector2i>>> available_ways;
		Board& ref;
		void choosePawn()
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
				//можно ли ходить на право
				if (x + 1 <= 7)
				{
					//можно ли поставить пешку справа
					if (ref.space[x + 1][y].player_2 != 1)
					{
						p.second.push_back({ x + 1,y });
					}
				}
				//можнно ли ходить на лево
				if (x - 1 >= 0)
				{
					if (ref.space[x - 1][y].player_2 != 1)
					{
						p.second.push_back({ x - 1,y });
					}
				}
				//можно ли ходить на верх
				if (y + 1 <= 7)
				{
					if (ref.space[x][y + 1].player_2 != 1)
					{
						p.second.push_back({ x,y + 1 });
					}
				}
				//можно ли ходить вниз
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
								if (ref.space[i][j].player_1 == 1 and way.x == i and way.y == j)//для читаемости
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

	}ai(b);



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
						if (b.space_cell(cursor.field_coord_clamp).player_1 == 1)//==1 излишне, но для читаемости
						{
							for (int i = 0; i < b.player_1.size(); ++i)
							{
								if (b.player_1[i].position == cursor.field_coord_clamp)//Мышь наведена на i пешку
								{
									render.add_UI_helper(UI_helperCell(cursor.field_coord_clamp.x, cursor.field_coord_clamp.y, UI_helperCell::color::yellow));//Создаем подсказку, какую пешку выбрал игрок
									player1.choosed_pawn = cursor.field_coord_clamp;



									//test available ways
									auto find_available_ways_for_choosed_pawn = [&b, &player1]
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
									}; find_available_ways_for_choosed_pawn();//Проверяем.

									for (auto& el : player1.available_ways)
									{
										render.add_UI_helper(UI_helperCell(el.x, el.y, UI_helperCell::color::green));//добавляем подсказки для доступных ходов
									}
									current_state = state::pl1_choosing_way;

									break;//выход из цикла;
								}
							}
						}
					}
				}
				break;//выхода из case
			}
			case state::pl1_choosing_way:
			{
				if (ev.type == sf::Event::EventType::MouseButtonPressed)
				{
					if (ev.mouseButton.button == sf::Mouse::Button::Left)
					{
						if (player1.choosed_pawn == cursor.field_coord)//Повторное нажатие на выбранную пешку - отменяет выбор
						{
							render.remove_UI_helpers();
							player1.available_ways.clear();
							current_state = state::pl1_choosing_pawn;
							break;//выход из case
						}


						bool correct_click = false;
						for (int i = 0; i < player1.available_ways.size(); ++i)
						{
							if (cursor.field_coord_clamp == player1.available_ways[i])//нашли куда перемещать пешку
							{
								correct_click = true;
								for (auto& el : b.player_2)//Восстанавливаем позицию текстуры у чужой пешки, если она стоит в той же, что и выбранная для перемещения
								{
									if (el.position == player1.choosed_pawn)
									{
										el.setPosition_as_default();
										break;
									}
								}


								b.space_cell(player1.choosed_pawn).player_1 = 0; 
								b.space_cell(cursor.field_coord_clamp).player_1 = 1;

								for (auto& el : b.player_1)//ищем объект пешки, которую будем перемещать.
								{
									if (el.position == player1.choosed_pawn)
									{
										
										el.setPosition(cursor.field_coord_clamp);
										for (auto& el_2 : b.player_2)//если в позиции две пешки, то делаем сдвиг их текстуры
										{
											if (el_2.position == el.position)
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
						if (!correct_click)
						{
							break;
						}


						render.remove_UI_helpers();
						player1.available_ways.clear();
						if (b.checkWinner())
						{
							current_state = state::win_pl1;
						}
						else
						{
							current_state = state::pl2_choosing_pawn;//
						}
						break;


					}

				}
				break;

			}


			}
		}
		switch (current_state)
		{
		case state::pl2_choosing_pawn:
		{
			ai.choosePawn();
			render.add_UI_helper(ai.choosed_pawn->first->position.x, ai.choosed_pawn->first->position.y, UI_helperCell::color::yellow);
			current_state = pl2_choosing_way;
			break;
		}
		case state::pl2_choosing_way:
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));//emulation of thinking ai

			for (auto& el : b.player_1)//Восстанавливаем положение текстуры пешки, которая стояла вместе;
			{
				if (el.position == ai.choosed_pawn->first->position)
				{
					el.setPosition_as_default();
				}
			}

			b.space_cell(ai.choosed_pawn->first->position).player_2 = 0;
			b.space_cell(ai.choosed_pawn->second.front()).player_2 = 1;


			ai.choosed_pawn->first->setPosition(ai.choosed_pawn->second.front());//not best way ???
			b.space_cell(ai.choosed_pawn->first->position).player_2 = 1;
			if (b.space_cell(ai.choosed_pawn->first->position).player_1 == 1)
			{
				ai.choosed_pawn->first->setPosition_as_black();
			}


			render.remove_UI_helpers();

			if (b.checkWinner())
			{
				current_state = state::win_pl2;
			}
			else
			{
				current_state = state::pl1_choosing_pawn;//
			}



			break;
		}
		}

		switch (current_state)
		{
		case state::win_pl1:
		{
			auto e = new EndingSprite(EndingSprite::type::win);
			render.add(*e);
			current_state = state::end;
			break;
		}
		case state::win_pl2:
		{
			auto e = new  EndingSprite(EndingSprite::type::lost);
			render.add(*e);
			current_state = state::end;
			break;
		}
		}



		render.update();
		b.debug();

	}
}
