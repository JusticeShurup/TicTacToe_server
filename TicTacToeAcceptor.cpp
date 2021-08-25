#include "TicTacToeAcceptor.h"

TicTacToeAcceptor::TicTacToeAcceptor(Poco::Net::ServerSocket& server_socket, Poco::Net::SocketReactor& reactor, Server* server) :
	SocketAcceptor(server_socket, reactor),
	server(server)
{}

ClientHandler* TicTacToeAcceptor::createServiceHandler(Poco::Net::StreamSocket& socket) {
	return new ClientHandler(socket, *reactor(), server);
}
