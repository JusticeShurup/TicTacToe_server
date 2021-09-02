#include "ClientHandler.h"
#include "TicTacToeAcceptor.h"
#include "Player.h"

ClientHandler::ClientHandler(Poco::Net::StreamSocket& client , Poco::Net::SocketReactor& reactor) :
    ClientHandler(client, reactor, nullptr) 
{
    throw std::logic_error("This should not be happening");
}

ClientHandler::ClientHandler(Poco::Net::StreamSocket& client, Poco::Net::SocketReactor& reactor, Server* server) :
	socket(client),
	reactor(reactor),
	server(server),
	player(new Player(client, server))
{
    server->addPlayer(client, player);

    reactor.addEventHandler(
        client,
        Poco::Observer<ClientHandler, Poco::Net::ReadableNotification>(
            *this,
            &ClientHandler::handleRead
            )
    );

    reactor.addEventHandler(
        client,
        Poco::Observer<ClientHandler, Poco::Net::ErrorNotification>(
            *this,
            &ClientHandler::handleError
            )
    );
}

ClientHandler::~ClientHandler() {
    reactor.removeEventHandler(
        socket,
        Poco::Observer<ClientHandler, Poco::Net::ErrorNotification>(
            *this,
            &ClientHandler::handleError
            )
    );

    reactor.removeEventHandler(
        socket,
        Poco::Observer<ClientHandler, Poco::Net::ReadableNotification>(
            *this,
            &ClientHandler::handleRead
            )
    );
}

void ClientHandler::handleRead(Poco::Net::ReadableNotification* notification) {
    notification->release();
    try {
        player->handleRead(socket);
    }
    catch (...) {
        handleClose();
    }
}

void ClientHandler::handleError(Poco::Net::ErrorNotification* notification) {
    notification->release();
    handleClose();
}

void ClientHandler::handleClose() {
    socket.close();
    delete this;
}

