#include "WaitForReadyGameState.h"
#include "Player.h"
#include "Game.h"
#include "WaitSecondPlayerState.h"

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
		else{
			std::cout << player->getNickname() << " is not ready" << std::endl;
			player->set_ready(0);
		}
		if (player->getGame()->isReady()) {
			std::cout << "Game is ready" << std::endl;
			uint8_t message = 1; // Game is ready, client can switch to game_screen
			uint8_t player_number; 
			if (player->get_gameNumber() == 1) {
				player->getGame()->getPlayer(1)->getSock().sendBytes(&message, sizeof(uint8_t));
				player_number = player->getGame()->getPlayer(1)->get_gameNumber();
				player->getGame()->getPlayer(1)->getSock().sendBytes(&player_number, sizeof(uint8_t));
			}
			else {
				player->getGame()->getPlayer(0)->getSock().sendBytes(&message, sizeof(uint8_t));
				player_number = player->getGame()->getPlayer(0)->get_gameNumber();
				player->getGame()->getPlayer(0)->getSock().sendBytes(&player_number, sizeof(uint8_t));
			}
			socket.sendBytes(&message, sizeof(uint8_t));
			player_number = player->get_gameNumber();
			player->getSock().sendBytes(&player_number, sizeof(uint8_t));
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
