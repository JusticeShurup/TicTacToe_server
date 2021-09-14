#include "ClientConnectedState.h"
#include "CreateGameState.h"
#include "JoinGameState.h"
#include "Player.h"
#include "Server.h"

ClientConnectedState::ClientConnectedState(Player* player) :
	State(player)
{}

void ClientConnectedState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t player_name_size = 0;
	socket.receiveBytes(&player_name_size, sizeof(player_name_size));
	std::string player_name(player_name_size, ' ');
	socket.receiveBytes(&(player_name[0]), player_name_size);
	player->getServer()->getPlayerBySocket(socket)->setNickname(player_name);
	std::cout << player_name << std::endl;
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
