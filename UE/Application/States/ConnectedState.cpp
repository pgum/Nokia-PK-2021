#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "TalkingState.h"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleCallRequest(common::PhoneNumber from) {
    context.user.showCalling(from);
    //TODO: timerStart
}

void ConnectedState::handleAcceptCall(common::PhoneNumber from){
    context.setState<TalkingState>();
}

}
