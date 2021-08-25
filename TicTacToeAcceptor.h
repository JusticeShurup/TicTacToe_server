#pragma once

#include "ClientHandler.h"
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>

class Server;

class TicTacToeAcceptor : public Poco::Net::SocketAcceptor<ClientHandler> {
public:
	TicTacToeAcceptor(Poco::Net::ServerSocket &server_socket, Poco::Net::SocketReactor &reactor, Server* server);

protected:
	virtual ClientHandler* createServiceHandler(Poco::Net::StreamSocket& socket) override;

private:
	Server* server;
};
