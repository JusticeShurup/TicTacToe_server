#include "ClientConnectedState.h"
#include "CreateGameState.h"
#include "JoinGameState.h"
#include "Player.h"
#include "Server.h"
#include <iostream>

ClientConnectedState::ClientConnectedState(Player* player) :
	State(player), 
	buffer{0}
{}

void ClientConnectedState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t player_name_size = 0;
	
	receiveNameBytes(buffer);

	player->setNickname(buffer+1);
	uint8_t message;
	socket.receiveBytes(&message, sizeof(uint8_t));
	switch (message) {
	case CREATE_NEW_GAME_MSG:
		player->setState(new CreateGameState(player));
		std::cout << "I am here" << std::endl;
		break;

	case JOIN_GAME_MSG:
		player->setState(new JoinGameState(player));
		std::cout << "Here" << std::endl;
		break;

	default:
		handleInvalidMessage(socket);
	}
}
