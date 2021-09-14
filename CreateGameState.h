#pragma once

#include "State.h"

class CreateGameState : public State {
	static const int MAX_NAME_LENGTH = 128;

public:
	CreateGameState(Player* player);

	virtual void handleRead(Poco::Net::StreamSocket socket) override;

private:
	char name_buffer[MAX_NAME_LENGTH];
	int position;
};
