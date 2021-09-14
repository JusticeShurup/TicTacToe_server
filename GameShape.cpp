#include "GameShape.h"
#include <iostream>

GameShape::GameShape()
{
	enabled = false;
	player_number = 5;
}

void GameShape::set_enabled(bool flag) {
	enabled = flag;
}

bool GameShape::get_enabled() {
	return enabled;
}

int GameShape::get_player_number() {
	return player_number;
}

void GameShape::set_player_number(int player_number) {
	this->player_number = player_number;
}