#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include "GameShape.h"
#include "WaitSecondPlayerState.h"

GameState::GameState(Player* player) : 
	State(player),
	buffer{0}
{}

void GameState::handleRead(Poco::Net::StreamSocket socket) {
	uint8_t turn = 1;
	socket.receiveBytes(&turn, sizeof(uint8_t));
	for (int i = 0; i < 9; i++) {
		buffer[i] = player->getGame()->getGameShape(i)->get_enabled();
	}
	for (int i = 9; i < 18; i++) {
		buffer[i] = player->getGame()->getGameShape(i-9)->get_player_number();
	}
	socket.sendBytes(&buffer, 18);
	socket.sendBytes(&turn, sizeof(uint8_t));
	uint8_t game_shape_number;
	socket.receiveBytes(&game_shape_number, sizeof(uint8_t));
	
	player->getGame()->getGameShape(game_shape_number)->set_enabled(true);
	player->getGame()->getGameShape(game_shape_number)->set_player_number(player->get_gameNumber());

	if (player->get_gameNumber() == 1) {
		player->getGame()->getPlayer(1)->setState(new GameState(player->getGame()->getPlayer(1)));
		player->setState(new WaitSecondPlayerState(player));
	}
	else {
		player->getGame()->getPlayer(0)->setState(new GameState(player->getGame()->getPlayer(0)));
		player->setState(new WaitSecondPlayerState(player));
	}
}