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

	local_player player1;

	ai_player ai(b);


	bool cheat = false;
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
			if (ev.type == sf::Event::EventType::KeyPressed)
			{
				if (ev.key.code == sf::Keyboard::Key::F9)
				{
					cheat = true;
				}
			}
			switch (current_state)
			{
			case state::pl1_choosing_pawn:
			{
				if (ev.type == sf::Event::EventType::MouseButtonPressed)
				{
					if (ev.mouseButton.button == sf::Mouse::Button::Left)
					{
						if (b.space_cell(cursor.field_coord_clamp).player_1 == 1)
						{

								render.add_UI_helper(cursor.field_coord_clamp, UI_helperCell::color::yellow);//Создаем подсказку, какую пешку выбрал игрок
								player1.choosed_pawn = cursor.field_coord_clamp;

								//test available ways
								player1.FindAvailableWaysForChoosedPawn(b);

								for (auto& el : player1.available_ways)
								{
									render.add_UI_helper(el, UI_helperCell::color::green);//добавляем подсказки для доступных ходов
								}
								current_state = state::pl1_choosing_way;
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
						if (player1.HasAvailableWayWithCoord(cursor.field_coord_clamp))
						{
							if (auto pawn = b.getPlayer_2_PawnOnPosition(player1.choosed_pawn); pawn.has_value())
							{
								pawn.value().get().setPosition_as_default();
							}

							b.space_cell(player1.choosed_pawn).player_1 = 0;
							b.space_cell(cursor.field_coord_clamp).player_1 = 1;

							auto pawn_to_move = b.getPlayer_1_PawnOnPosition(player1.choosed_pawn);
							pawn_to_move.value().get().setPosition(cursor.field_coord_clamp);
							if (auto another_pawn = b.getPlayer_2_PawnOnPosition(cursor.field_coord_clamp); another_pawn.has_value())//если в новой позиции чужая пешка, то делаем сдвиг спрайта.
							{
								pawn_to_move.value().get().setPosition_as_white();
								another_pawn.value().get().setPosition_as_black();
							}
						}
						else
						{
							break;
						}


						render.remove_UI_helpers();

						if (!cheat)
						{
							player1.available_ways.clear();
						}

						if (b.checkWinner())
						{
							current_state = state::win_pl1;
						}
						else
						{
							current_state = state::pl2_choosing_pawn;//
						}
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
			render.add_UI_helper(ai.getChoosedPawnPos(), UI_helperCell::color::yellow);
			current_state = pl2_choosing_way;
			break;
		}
		case state::pl2_choosing_way:
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));//emulation of thinking ai

			if (auto pawn_to_move = b.getPlayer_1_PawnOnPosition(ai.getChoosedPawnPos()); pawn_to_move.has_value())
			{
				pawn_to_move.value().get().setPosition_as_default();
			}


			auto random_way_nomer = [rd = std::random_device()](decltype(ai.choosed_pawn)& pawn) mutable
			{
				int res;
				int modul = pawn->second.size();
				return rd() % modul;
			};


			int random_selected_way = random_way_nomer(ai.choosed_pawn);

			b.space_cell(ai.getChoosedPawnPos()).player_2 = 0;
			b.space_cell(ai.choosed_pawn->second[random_selected_way]).player_2 = 1;

			if (b.space_cell(ai.getChoosedPawnPos()).player_1 == 1)
			{
				//находим эту пешку в списке и восстанавливаем позицию спрайта
				auto pawn_to_move = b.getPlayer_1_PawnOnPosition(ai.getChoosedPawnPos());
				pawn_to_move.value().get().setPosition_as_default();
			}

			ai.moveSelectedPawn(random_selected_way);
			b.space_cell(ai.getChoosedPawnPos()).player_2 = 1;

			if (b.space_cell(ai.getChoosedPawnPos()).player_1 == 1)
			{
				ai.getChoosedPawnObj().setPosition_as_black();

				if (auto pawn_to_edit = b.getPlayer_1_PawnOnPosition(ai.getChoosedPawnPos()); pawn_to_edit.has_value())
				{
					pawn_to_edit.value().get().setPosition_as_white();
				}


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
			auto e = new EndingSprite(EndingSprite::type::lost);
			render.add(*e);
			current_state = state::end;
			break;
		}
		}
		render.update();
	}
}
