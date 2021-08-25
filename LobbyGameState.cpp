#include "LobbyGameState.h"
#include "Player.h"
#include "Server.h"
#include "Game.h"
#include "Poco/Net/StreamSocket.h"

LobbyGameState::LobbyGameState(Player* player) :
	State(player)
{
	Poco::Net::StreamSocket client;
	player->getGame()->addPlayer(new Player(client, player->getServer()));
}

void LobbyGameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t message = 2;
	char* buffer = new char[20];
	if (player->getServer()->getPlayerBySocket(socket)->get_gameNumber() != 0 && player->getGame()->getPlayer(1)) {
		std::string nickname;
		std::cout << "fuck" << std::endl;
		if (player->getServer()->getPlayerBySocket(socket)->get_gameNumber() == 1) {
			nickname = player->getGame()->getPlayer(1)->getNickname();
			strcpy(buffer, nickname.c_str());
		}
		else {
			nickname = player->getGame()->getPlayer(0)->getNickname();
			strcpy(buffer, nickname.c_str());
		}
		socket.sendBytes(buffer, 20);
	}
	std::cout << "nigga" << std::endl;
	delete buffer;
	/*
	if (message == READY_MSG) {
		player->getGame()->start();
	}
	else if (message == EXIT_MSG) {
		player->getGame();
	}
	*/
}