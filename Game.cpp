#include "Game.h"
#include "Player.h"
#include <stdexcept>
//#include "InGameState.h"

Game::Game(const std::string &name, Player* first_player) :
	name(name)
{
	players[0] = first_player;
	first_player->setGame(this);
	players[1] = nullptr;
}

void Game::start() {
	if (isReady()) {
		//players[0]->setState(new InGameState);
		//players[1]->setState(new InGameState);
	}
}

std::string Game::getName() const {
	return name;
}

Player* Game::getPlayer(int index) {
	if (index != 0 && index != 1) throw std::logic_error("Player must have index equals only to 0 or 1");
	return players[index];
}

void Game::addPlayer(Player* second_player) {
	if (players[1]) throw std::runtime_error("This game is already full");

	players[1] = second_player;
}

void Game::removePlayer(Player* player) {
	if (player == players[0]) {
		players[0] = nullptr;
	}
	else if(player == players[1]){
		players[1] = nullptr;
	}
	else {
		throw std::invalid_argument("This player is not in the game");
	}
}

bool Game::isReady() const {
	return players[0] && players[1];
}
