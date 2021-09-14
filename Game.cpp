#include "Game.h"
#include "Player.h"
#include <stdexcept>
#include "GameState.h"
#include "WaitSecondPlayerState.h"

Game::Game(const std::string &name, Player* first_player) :
	name(name), 
	game_shapes{new GameShape}
{
	turns = 0;
	players[0] = first_player;
	first_player->setGame(this);
	players[1] = nullptr;
	for (auto& i : game_shapes) i = new GameShape;
}

void Game::start() {
	if (isReady()) {
		turns = 1;
		players[0]->setState(new GameState(players[0]));
		players[1]->setState(new WaitSecondPlayerState(players[1]));
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
	return players[0]->get_ready() && players[1]->get_ready();
}

GameShape* Game::getGameShape(int gameShape_number) {
	return game_shapes[gameShape_number];
}
