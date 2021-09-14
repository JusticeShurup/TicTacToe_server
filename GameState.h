#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "State.h"
class GameState :
    public State
{
public:
	GameState(Player* player);

	virtual void handleRead(Poco::Net::StreamSocket socket) override;
private:
	char buffer[18];
};
#endif
