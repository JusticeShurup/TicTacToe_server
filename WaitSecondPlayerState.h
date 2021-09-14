#ifndef _WAIT_SECOND_PLAYER_STATE_H_
#define _WAIT_SECOND_PLAYER_STATE_H_
#include "State.h"
class WaitSecondPlayerState :
    public State
{
public: 
    WaitSecondPlayerState(Player* player);

    virtual void handleRead(Poco::Net::StreamSocket player) override;
};
#endif
