#include "ChessGame.hpp"

sf::RenderWindow window(sf::VideoMode(1080, 1080), "ChessGame");

int main()
{

	RenderSystem render(window);

	Board f{render};


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



		}
		
		std::cout << cursor.raw.x << ' ' << cursor.raw.y << '\n';

		render.update();


	}
}
