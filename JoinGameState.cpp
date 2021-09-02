#include "JoinGameState.h"
#include "LobbyGameState.h"
#include "Player.h"
#include "Server.h"
#include "Game.h"
#include <stdexcept>

JoinGameState::JoinGameState(Player* player) :
	State(player),
	position(0),
	name_buffer{0}
{
}

void JoinGameState::handleRead(Poco::Net::StreamSocket socket) {
	int actually_read = socket.receiveBytes(name_buffer + position, MAX_NAME_LENGTH + 1 - position);
	int bytes_to_read = name_buffer[0];
	if (bytes_to_read > MAX_NAME_LENGTH || bytes_to_read < 1) {
		handleInvalidMessage(socket);
		return;
	}

	position += actually_read;

	if (position > bytes_to_read) {
		std::string name(name_buffer + 1, bytes_to_read);
		Server* server = player->getServer();
		try {
			Game* game = server->getGame(name);
			game->addPlayer(player);
			player->setGame(game);
		}
		catch (std::runtime_error& e) {  // TODO: make distinct exceptions
			position = 0;
			uint8_t result = 0;
			socket.sendBytes(&result, sizeof(uint8_t));
			return;
		}
		uint8_t result = 1;
		player->getServer()->getPlayerBySocket(socket)->set_gameNumber(2);
		socket.sendBytes(&result, sizeof(uint8_t));
		uint8_t size = name.size();
		socket.sendBytes(&size, sizeof(uint8_t));
		socket.sendBytes(name.c_str(), name.size());
		player->setState(new LobbyGameState(player));
		// TODO: change state

	}
}
