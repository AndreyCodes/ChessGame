#include"../Include/RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow& ref) : window{ ref } {	}

void RenderSystem::setBoardTexture(IRenderable& board)
{
	board_sprite = &board;
}

void RenderSystem::update()
{
	window.clear();
	window.draw(*board_sprite);

	for (auto& element : UI_helpers)
	{
		window.draw(element);
	}
	for (auto& element : objs)
	{

		window.draw(*element);
	}
	window.display();
}

void RenderSystem::add(IRenderable& some)
{
	objs.push_back(&some);
}



void RenderSystem::add_UI_helper(UI_helperCell some)
{
	UI_helpers.push_back(some);
}
void RenderSystem::add_UI_helper(int x, int y, UI_helperCell::color c)
{
	UI_helpers.emplace_back(x, y, c);
}
void RenderSystem::add_UI_helper(sf::Vector2i pos, UI_helperCell::color c)
{
	UI_helpers.emplace_back(pos.x, pos.y, c);
}

void RenderSystem::remove_UI_helpers()
{
	UI_helpers.clear();
}

void RenderSystem::remove(IRenderable& some)
{
	/*objs.erase(std::remove_if(objs.begin(), objs.end(),
					[&some](auto el){return el == &some;}),
											objs.end());*///сохраняет порядок объектов

	for (int i = 0; i < objs.size(); ++i)
	{
		if (objs[i] == &some)
		{
			objs[i] = objs.back();
			objs.pop_back();
			return;
		}
	}
	for (int i = 0; i < UI_helpers.size(); ++i)//shoul deprecate
	{
		if (&UI_helpers[i] == &some)
		{
			UI_helpers[i] = UI_helpers.back();
			UI_helpers.pop_back();
			return;
		}
	}
}