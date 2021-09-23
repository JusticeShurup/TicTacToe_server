#include "CreateGameState.h"
#include "Player.h"
#include "Server.h"
#include "Game.h"
#include <stdexcept>
#include <stdint.h>
#include "ClientConnectedState.h"
#include "WaitSecondPlayerState.h"
#include "LobbyGameState.h"
#include <iostream>

CreateGameState::CreateGameState(Player* player) :
	State(player),
	position(0), 
	name_buffer{0}
{}

void CreateGameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t result;
	int actually_read = socket.receiveBytes(name_buffer + position, MAX_NAME_LENGTH + 1 - position);
	int bytes_to_read = name_buffer[0];
	if (bytes_to_read > MAX_NAME_LENGTH || bytes_to_read < 1) {
		handleInvalidMessage(socket);
		return;
	}

	position += actually_read;
	if (position > bytes_to_read) {
		std::string name(name_buffer + 1, name_buffer[0]);
		std::cout << name  << " " << name.size() << std::endl;
		Server* server = player->getServer();
		if (!server->isGameNameFree(name)) {
			std::cout << "game is not free" << std::endl;
			position = 0;
			//uint8_t result = 1;
			//socket.sendBytes(&result, sizeof(uint8_t));
			return;
		}
		//Game* game = new Game(name, player);
		server->addGame(name, new Game(name, player));
		player->set_gameNumber(1);
		uint8_t size = name.size();
		
		sendNameBytes(name_buffer);

		player->setState(new WaitSecondPlayerState(player));
	}
}
