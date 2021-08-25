#include "ClientConnectedState.h"
#include "CreateGameState.h"
#include "JoinGameState.h"
#include "Player.h"

ClientConnectedState::ClientConnectedState(Player* player) :
	State(player)
{}

void ClientConnectedState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t message;
	socket.receiveBytes(&message, sizeof(uint8_t));

	switch (message) {
	case CREATE_NEW_GAME_MSG:
		player->setState(new CreateGameState(player));
		break;

	case JOIN_GAME_MSG:
		player->setState(new JoinGameState(player));
		break;

	default:
		handleInvalidMessage(socket);
	}
}
