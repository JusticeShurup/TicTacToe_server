#pragma once

#include "State.h"

class JoinGameState : public State {
	static const int MAX_NAME_LENGTH = 128;

public:
	JoinGameState(Player* player);

	virtual void handleRead(Poco::Net::StreamSocket socket) override;

private:
	char name_buffer[MAX_NAME_LENGTH];
	int position;
};
