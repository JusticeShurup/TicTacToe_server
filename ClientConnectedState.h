#pragma once

#include "State.h"
#include <stdint.h>

class Player;

class ClientConnectedState : public State {
	static const uint8_t CREATE_NEW_GAME_MSG = 1;
	static const uint8_t JOIN_GAME_MSG = 2;

public:
	ClientConnectedState(Player* player);

	virtual void handleRead(Poco::Net::StreamSocket socket) override;
private: 
	char buffer[18];
};
