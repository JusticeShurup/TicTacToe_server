#include "Server.h"
#include "TicTacToeAcceptor.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>
#include <iostream>


int main() {
    Poco::Net::ServerSocket server_socket(1337);
    Poco::Net::SocketReactor reactor;
    //Poco::Net::SocketAcceptor<EchoHandler> acceptor(server_socket, reactor);
    Server server;
    TicTacToeAcceptor acceptor(server_socket, reactor, &server);

    reactor.run();

    return 0;
}
