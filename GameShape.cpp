#include "GameShape.h"

GameShape::GameShape(int startX, int endX, int startY, int endY)
	: startX(startX), 
	endX(endX),
	startY(startY),
	endY(endY)
{
	enabled = false;
	player_number = 0;
}

int GameShape::get_player_number() {
	return player_number;
}