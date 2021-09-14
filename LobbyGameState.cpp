#include "LobbyGameState.h"
#include "ClientConnectedState.h"
#include "Player.h"
#include "Server.h"
#include "Game.h"
#include "Poco/Net/StreamSocket.h"
#include <stdint.h>
#include <string>
#include <iostream>
#include "WaitForReadyGameState.h"

LobbyGameState::LobbyGameState(Player* player) :
	State(player)
{
}

void LobbyGameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t message;
	socket.receiveBytes(&message, sizeof(uint8_t));
	std::string nickname;
	uint8_t size;
	if (player->getGame()->getPlayer(1)) {
		message = 1;
		socket.sendBytes(&message, sizeof(uint8_t));
		if (player->getServer()->getPlayerBySocket(socket)->get_gameNumber() == 1) {
			size = player->getGame()->getPlayer(1)->getNickname().size();
			nickname = player->getGame()->getPlayer(1)->getNickname().c_str();
		}
		else {
			size = player->getGame()->getPlayer(0)->getNickname().size();
			nickname = player->getGame()->getPlayer(0)->getNickname().c_str();
		}
		socket.sendBytes(&size, sizeof(uint8_t));
		socket.sendBytes(nickname.c_str(), nickname.size());
	}
	player->setState(new WaitForReadyGameState(player));
}