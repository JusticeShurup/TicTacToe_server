#pragma once

#include "Server.h"
#include "Player.h"
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketNotification.h>

class ClientHandler{
public:
	ClientHandler(Poco::Net::StreamSocket& client, Poco::Net::SocketReactor& reactor);
	ClientHandler(Poco::Net::StreamSocket& client, Poco::Net::SocketReactor& reactor, Server* server);
	~ClientHandler();

private:
	void handleRead(Poco::Net::ReadableNotification* notification);
	void handleError(Poco::Net::ErrorNotification* notification);
	void handleClose();

	Poco::Net::StreamSocket socket;
	Poco::Net::SocketReactor& reactor;
	Server* server;
	Player* player;
};
