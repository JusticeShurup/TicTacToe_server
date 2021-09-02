#pragma once

#include <string>

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


private:
	std::string name;
	Player* players[2];
};
