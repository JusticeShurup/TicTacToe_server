#pragma once

#include <string>
#include "GameShape.h"

class Player;

class Game {
public:
	Game(const std::string &name, Player* first_player);

	void start();

	std::string getName() const;

	Player* getPlayer(int index);
	
	void addPlayer(Player* second_player);
	void removePlayer(Player* player);

	bool isReady() const;

	GameShape* getGameShape(int gameShape_number);

	int turns; // quantity of turns
private:
	GameShape* game_shapes[9];
	std::string name;
	Player* players[2];
};
