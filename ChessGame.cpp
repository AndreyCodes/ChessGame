#include "ChessGame.hpp"

struct IRenderable
{
	virtual operator sf::Drawable& () = 0;
};

struct Pawn: IRenderable
{
	enum class owner_tag
	{
		player,
		ai
	};
	int x, y;
	owner_tag owner;
	sf::RectangleShape representation;
	sf::Texture texture;
	Pawn(int x_, int y_, owner_tag ow, sf::Texture&& tex) : x{ x_ }, y{ y_ }, owner{ ow }
	{
		texture.swap(tex);
		representation.setTexture(&texture);
		representation.setSize(sf::Vector2f(texture.getSize()));
	}
	void setPosition(sf::Vector2f v)//set only view position
	{
		representation.setPosition(v + position_offset);
	}
	const static inline sf::Vector2f position_offset{ 32,8 };
};

struct Field: IRenderable
{
private:
	struct Cell
	{
		bool player;
		bool ai;
	};
	Cell space[8][8];

	sf::Sprite board_sprite;
	sf::Texture board_texture;

public:
	Field(sf::Texture&& t)//to own resource
	{
		board_texture.swap(t);
		board_sprite.setTexture(board_texture);
	}
	operator sf::Drawable& () override
	{
		return board_sprite;
	}
};

struct RenderSystem
{
protected:
	std::vector<IRenderable*> objs;
	sf::RenderWindow& window;
	RenderSystem(sf::RenderWindow& ref): window{ref}{}

public:
	RenderSystem(sf::RenderWindow& ref, IRenderable& field_sprite): window{ref}
	{
		add(field_sprite);//инвариант. чтобы всегда рисовалось поверх доски.
	}

	void update()
	{
		window.clear();
		for (auto& element : objs)
		{
			window.draw(*element);
		}
		window.display();
	}
	void add(IRenderable& some)
	{
		objs.push_back(&some);
	}
	void remove(IRenderable& some)
	{
		/*objs.erase(std::remove_if(objs.begin(), objs.end(),
						[&some](auto el){return el == &some;}),
												objs.end());*///сохраняет порядок объектов

		for (int i = 0; i < objs.size(); ++i)
		{
			if (objs[i] == &some)
			{
				objs[i] == objs.back();
				objs.pop_back();
				return;
			}
		}
	}
};

struct MouseCoord
{
	const static inline sf::Vector2i offset{ 36,36 };

	sf::Vector2i raw;
	sf::Vector2i discrete;
	sf::Vector2i field_coord;
	MouseCoord(sf::RenderWindow& ref)
	{
		raw = sf::Mouse::getPosition(ref);
		field_coord = (raw-offset) / 126;
		discrete = field_coord * 126;
	}
};



int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 1080), "ChessGame");
	Field f([] {sf::Texture t; t.loadFromFile("gamedata/Board.png"); return t; }());

	RenderSystem render(window, f);


	while (window.isOpen())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::EventType::Closed)
			{
				window.close();
			}




		}
		MouseCoord cursor(window);
		std::cout << cursor.field_coord.x << ' ' << cursor.field_coord.y << '\n';


		render.update();


	}
}
