#pragma once
#include "State.h"
class WaitForReadyGameState :
    public State
{
public:
	WaitForReadyGameState(Player* player);

	virtual void handleRead(Poco::Net::StreamSocket socket) override;
private: 
	static const uint8_t READY_MSG = 1;
	static const uint8_t EXIT_MSG = 2;
};

