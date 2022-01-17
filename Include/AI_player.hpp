#include<vector>

#include"Board.hpp"


struct ai_player
{
	std::pair<Pawn*, std::vector<sf::Vector2i>>* choosed_pawn;
	std::vector < std::pair<Pawn*, std::vector<sf::Vector2i>>> available_ways;
	Board& ref;

	ai_player(Board& ref_);
	void choosePawn();
	void moveSelectedPawn(int num_of_available_way);

	sf::Vector2i getChoosedPawnPos();

	Pawn& getChoosedPawnObj();


};