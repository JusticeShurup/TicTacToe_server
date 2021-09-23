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
	State(player), 
	buffer{0}
{
}

void LobbyGameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t message;
	socket.receiveBytes(&message, sizeof(uint8_t));
	std::string nickname;
	uint8_t size;
	
	Player* second_player = player->getGame()->getPlayer(2 - player->get_gameNumber());
	nickname = second_player->getNickname();
	size = nickname.size();
	*((uint8_t*)buffer) = size;
	strcpy(buffer + sizeof(uint8_t), nickname.c_str());

	sendNameBytes(buffer);
	
	player->setState(new WaitForReadyGameState(player));
}