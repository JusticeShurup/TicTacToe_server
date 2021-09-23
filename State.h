#pragma once

#include <Poco/Net/StreamSocket.h>
class Player;

class State {
public:
	State(Player *player);
	virtual ~State();

	virtual void handleRead(Poco::Net::StreamSocket socket) = 0;
	
	void sendNameBytes(char (&buffer)[18]);
	void receiveNameBytes(char (&buffer)[18]);

protected:
	void handleInvalidMessage(Poco::Net::StreamSocket socket);

	Player* player;
};
