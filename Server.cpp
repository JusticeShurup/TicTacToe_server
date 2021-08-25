#include "Server.h"
#include "Player.h"
#include "Game.h"
#include <stdexcept>

void Server::addPlayer(const Poco::Net::StreamSocket& socket, Player* player) {
	auto it = players.find(socket);
	if (it != players.end()) throw std::runtime_error("Client already cpnnected");

	players[socket] = player;
}

Player* Server::getPlayerBySocket(const Poco::Net::StreamSocket& socket) const {
	auto it = players.find(socket);
	if (it == players.end()) throw std::runtime_error("No player is associated with this socket");

	return it->second;
}

void Server::removePlayerBySocket(const Poco::Net::StreamSocket& socket) {
	Player* player = getPlayerBySocket(socket);
	players.erase(socket);

	if (player) {
		Game* game = player->getGame();
		if (game) {
			removeGame(game->getName());
		}
	}
}

bool Server::isGameNameFree(const std::string& name) const {
	return games.find(name) == games.end();
}

void Server::addGame(const std::string& name, Game* game) {
	auto it = games.find(name);
	if (it != games.end()) throw std::runtime_error("Game with such name already exists");

	games[name] = game;
}

Game* Server::getGame(const std::string& name) const {
	auto it = games.find(name);
	if (it == games.end()) throw std::runtime_error("No such game");

	return it->second;
}

void Server::removeGame(const std::string& name) {
	games.erase(name);
}
