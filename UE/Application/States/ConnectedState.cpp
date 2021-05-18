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
}

void ConnectedState::handleAcceptCall(common::PhoneNumber from){
    context.setState<TalkingState>(from);
}

void ConnectedState::handleRejectCall(common::PhoneNumber from){
    context.user.showConnected();
    context.bts.sendCallRespond(context.phoneNumber,from,
                                common::MessageId::CallDropped);
}

void ConnectedState::handleSendCallRequest(common::PhoneNumber to) {
    context.bts.sendCallRequest(context.phoneNumber,to);
}
}
