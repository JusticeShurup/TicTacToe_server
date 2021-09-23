#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include "GameShape.h"
#include "WaitSecondPlayerState.h"
#include <iostream>

GameState::GameState(Player* player) : 
	State(player),
	buffer{0}
{}

void GameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t turn;
	uint8_t game_shape_number;
	socket.receiveBytes(&game_shape_number, sizeof(uint8_t));
	player->getGame()->turns++;
	std::cout << player->getGame()->turns << std::endl;
	

	player->getGame()->getGameShape(game_shape_number)->set_enabled(true);
	player->getGame()->getGameShape(game_shape_number)->set_player_number(player->get_gameNumber());

	for (int i = 0; i < 9; i++) {
		std::cout << player->getGame()->getGameShape(i)->get_enabled() << " " << player->getGame()->getGameShape(i)->get_player_number() << std::endl;
		buffer[i] = player->getGame()->getGameShape(i)->get_player_number();
	}
	std::cout << std::endl;
	socket.sendBytes(&buffer, 9);
	turn = 1;
	player->getGame()->getPlayer(2 - player->get_gameNumber())->getSock().sendBytes(&buffer, 9);
	std::cout << "sent buffer" << std::endl;
	player->getGame()->getPlayer(2 - player->get_gameNumber())->getSock().sendBytes(&turn, sizeof(uint8_t));


	player->getGame()->getPlayer(2 - player->get_gameNumber())->setState(new GameState(player->getGame()->getPlayer(2 - player->get_gameNumber())));
	player->setState(new WaitSecondPlayerState(player));
}