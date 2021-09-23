#include "State.h"
#include "Player.h"
#include "Server.h"

State::State(Player* player) :
	player(player)
{}

State::~State() {
	// empty
}

void State::sendNameBytes(char (&buffer)[18]) {
	Poco::Net::StreamSocket socket = player->getSock();
	int total_sent = 0;
	int buffer_length = 18;
	while (total_sent < buffer_length) {
		int actually_sent = socket.sendBytes(

			buffer + total_sent,
			buffer_length - total_sent
		);
		total_sent += actually_sent;
	}
}

void State::receiveNameBytes(char(&buffer)[18]) {
	Poco::Net::StreamSocket socket = player->getSock();
	int total_received = 0;
	while (total_received < 18) {
		int actually_received = socket.receiveBytes(
			buffer + total_received,
			18 - total_received
		);
		total_received += actually_received;
	}
}

void State::handleInvalidMessage(Poco::Net::StreamSocket socket) {
	player->getServer()->removePlayerBySocket(socket);
	socket.shutdown();
	socket.close();
}
