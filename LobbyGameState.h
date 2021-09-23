#ifndef _STATE_H_
#define _STATE_H_
#include "State.h"
class LobbyGameState :
    public State
{
    const int READY_MSG = 1; 
    const int EXIT_MSG = 2;
public: 
    LobbyGameState(Player* player);

    virtual void handleRead(Poco::Net::StreamSocket socket) override;

private:
    char buffer[18];
};
#endif

