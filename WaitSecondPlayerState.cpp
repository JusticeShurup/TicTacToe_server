#include "WaitSecondPlayerState.h"
WaitSecondPlayerState::WaitSecondPlayerState(Player* player) :
	State(player)
{}

void WaitSecondPlayerState::handleRead(Poco::Net::StreamSocket socket) {

}
