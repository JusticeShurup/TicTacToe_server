#ifndef _GAMESHAPE_H_
#define _GAMESHAPE_H_
class GameShape
{
public:
	GameShape();

	void set_enabled(bool flag);
	bool get_enabled();

	int get_player_number();
	void set_player_number(int player_number);
private: 

	int player_number;
	bool enabled;
};
#endif