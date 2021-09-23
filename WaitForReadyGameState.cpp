#include "WaitForReadyGameState.h"
#include "Player.h"
#include "Game.h"
#include "WaitSecondPlayerState.h"
#include <iostream>

WaitForReadyGameState::WaitForReadyGameState(Player* player) : State(player) {}

void WaitForReadyGameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t message;
	socket.receiveBytes(&message, sizeof(uint8_t));
	switch (message){
	case READY_MSG:
		if (!player->get_ready()) {
			std::cout << player->getNickname() << " is ready" << std::endl;
			player->set_ready(1);
		}
		else {
			std::cout << player->getNickname() << " is not ready" << std::endl;
			player->set_ready(0);
		}
		if (player->getGame()->isReady()) {
			std::cout << "Game is ready" << std::endl;
			uint8_t message = 1; // Game is ready, client can switch to game_screen
			uint8_t player_number;
			Player* second_player = player->getGame()->getPlayer(2 - player->get_gameNumber());
			player->getSock().sendBytes(&message, sizeof(uint8_t));
			second_player->getSock().sendBytes(&message, sizeof(uint8_t));
			std::cout << player->get_gameNumber() << " " << second_player->get_gameNumber() << std::endl;

			player_number = second_player->get_gameNumber();
			second_player->getSock().sendBytes(&player_number, sizeof(uint8_t));
			message = (second_player->get_gameNumber() == 1 ? 1 : 0);
			second_player->getSock().sendBytes(&message, sizeof(uint8_t));

			player_number = player->get_gameNumber();
			socket.sendBytes(&player_number, sizeof(uint8_t));
			message = (player->get_gameNumber() == 1 ? 1 : 0);
			player->getSock().sendBytes(&message, sizeof(uint8_t));


			player->getGame()->start();
		}
		break;
	case EXIT_MSG:
		handleInvalidMessage(socket);
		break;
	default:
		handleInvalidMessage(socket);
	}

}
