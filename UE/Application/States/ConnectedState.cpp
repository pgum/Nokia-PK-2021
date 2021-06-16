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
        context.timer.startTimer(30s);
}
void ConnectedState::handleReceivedCallAccept(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.setState<TalkingState>(from);
}

void ConnectedState::handleReceivedCallReject(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.user.alertUser("Call Dropped by "+to_string(from));
}

void ConnectedState::handleTimeout() {
    context.timer.stopTimer();
    context.user.alertUser("User does not respond");
}

void ConnectedState::handleCallRequest(common::PhoneNumber from) {
    context.user.showCalling(from);
}

void ConnectedState::handleSendCallAccepted(common::PhoneNumber from){
    context.timer.stopTimer();
    context.bts.sendCallAccept(from);
    context.setState<TalkingState>(from);
}

void ConnectedState::handleSendCallDropped(common::PhoneNumber from){
    context.timer.stopTimer();
    context.bts.sendCallDropped(from);
    context.user.showConnected();
}
void ConnectedState::handleUnknownRecipientSMS() {
    context.smsDb.unknownRecipientSms();
}

void ConnectedState::handleUnknownRecipient() {
    context.timer.stopTimer();
    context.user.alertUser("User unreachable");
}

}
