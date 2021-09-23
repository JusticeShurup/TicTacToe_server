#include "JoinGameState.h"
#include "LobbyGameState.h"
#include "Player.h"
#include "Server.h"
#include "Game.h"
#include "WaitSecondPlayerState.h"
#include <stdexcept>
#include <iostream>

JoinGameState::JoinGameState(Player* player) :
	State(player),
	position(0),
	name_buffer{0}
{}

void JoinGameState::handleRead(Poco::Net::StreamSocket socket) {
	int actually_read = socket.receiveBytes(name_buffer + position, MAX_NAME_LENGTH + 1 - position);
	int bytes_to_read = name_buffer[0];
	if (bytes_to_read > MAX_NAME_LENGTH || bytes_to_read < 1) {
		handleInvalidMessage(socket);
		return;
	}

	position += actually_read;

	if (position > bytes_to_read) {
		std::string name(name_buffer + 1, name_buffer[0]);
		std::cout << name << " " << name.size() << std::endl;
		Server* server = player->getServer();
		try {
			Game* game = server->getGame(name);
			game->addPlayer(player);
			player->setGame(game);
		}
		catch (std::runtime_error& e) {  // TODO: make distinct exceptions
			std::cout << e.what() << std::endl;
			position = 0;
			uint8_t result = 0;
			socket.sendBytes(&result, sizeof(uint8_t));
			return;
		}
		uint8_t result = 1;
		player->set_gameNumber(2);
		socket.sendBytes(&result, sizeof(uint8_t));
		std::cout << "no cringe" << std::endl;

		sendNameBytes(name_buffer);

		player->getGame()->getPlayer(0)->setState(new LobbyGameState(player->getGame()->getPlayer(0)));
		player->setState(new LobbyGameState(player));

	}
}
