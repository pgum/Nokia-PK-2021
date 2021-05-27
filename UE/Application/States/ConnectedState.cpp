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

void ConnectedState::handleSendCallRequest(common::PhoneNumber to) {
        context.bts.sendCallRequest(to);
        context.user.waitingForCallRespond();
        using namespace std::chrono_literals;
        context.timer.startTimer(60s);
}
void ConnectedState::handleReceivedCallAccept(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.setState<TalkingState>();
}

void ConnectedState::handleReceivedCallReject(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.user.alertUser("Call rejected");
}

void ConnectedState::handleTimeout() {
    context.timer.stopTimer();
    context.user.alertUser("User does not respond");
}

void ConnectedState::handleCallRequest(common::PhoneNumber from) {
        context.user.showCalling(from);
}

void ConnectedState::handleSendCallAccepted(common::PhoneNumber from){
    context.bts.sendCallAccept(from);
    context.setState<TalkingState>();
}

void ConnectedState::handleSendCallDropped(common::PhoneNumber from){
    context.bts.sendCallDropped(from);
    context.user.showConnected();
}


}
