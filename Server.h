#pragma once

#include <Poco/Net/StreamSocket.h>
#include <string>
#include <map>

class Player;
class Game;

class Server {
public:
	void addPlayer(const Poco::Net::StreamSocket& socket, Player* player);
	Player* getPlayerBySocket(const Poco::Net::StreamSocket& socket) const;
	void removePlayerBySocket(const Poco::Net::StreamSocket& socket);

	bool isGameNameFree(const std::string& name) const;

	void addGame(const std::string& name, Game* game);
	Game* getGame(const std::string& name) const;
	void removeGame(const std::string& name);

private:
	std::map<Poco::Net::StreamSocket, Player*> players;
	std::map<std::string, Game*> games;
};
