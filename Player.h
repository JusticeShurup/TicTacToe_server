#pragma once

#include "State.h"
#include <Poco/Net/StreamSocket.h>

class Server;
class Game;

class Player {
public:
	Player(Poco::Net::StreamSocket &client, Server *server);
	~Player();

	void setState(State* new_state);

	Server* getServer() const;
	Game* getGame() const;
	void setGame(Game* game);

	void setNickname(std::string nickname);
	std::string getNickname() const;
	
	void handleRead(Poco::Net::StreamSocket socket);

	bool get_ready() const;
	void set_ready(bool is_ready);

	int get_gameNumber() const;
	void set_gameNumber(int game_number);

	Poco::Net::StreamSocket& getSock();
private:
	Poco::Net::StreamSocket socket;
	std::string nickname;
	Server* server;
	Game* game;
	State* state;
	bool is_ready;
	int game_number; 
};
