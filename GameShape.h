#ifndef _GAMESHAPE_H_
#define _GAMESHAPE_H_
class GameShape
{
public:
	GameShape(int startX, int endX, int startY, int endY);
	bool isClicked(int posX, int posY, int player_number);
	int get_player_number();
private: 

	int startX;
	int endX;
	int startY;
	int endY;

	int player_number;
	bool enabled;
};
#endif