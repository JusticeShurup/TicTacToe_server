#include "State.h"
#include "Player.h"
#include "Server.h"

State::State(Player* player) :
	player(player)
{}

State::~State() {
	// empty
}

void State::handleInvalidMessage(Poco::Net::StreamSocket socket) {
	player->getServer()->removePlayerBySocket(socket);
	socket.shutdown();
	socket.close();
}
