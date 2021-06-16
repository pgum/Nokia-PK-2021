
#include "TalkingState.h"
#include "ConnectedState.hpp"

namespace ue
{
TalkingState::TalkingState(Context &context,common::PhoneNumber partnerPhoneNumber)
    : BaseState(context,"TalkingState")
    {

        context.user.setCallMode(partnerPhoneNumber);
        using namespace std::chrono_literals;
        context.timer.startTimer(120s);
    }

void TalkingState::handleSendCallTalk(common::PhoneNumber to, const std::string &msg)
{
    context.timer.stopTimer();
    context.bts.sendCallTalk(to,msg);
    using namespace std::chrono_literals;
    context.timer.startTimer(120s);
}
void TalkingState::handleSendCallDropped(common::PhoneNumber from)
{
    context.timer.stopTimer();
    context.bts.sendCallDropped(from);
    context.setState<ConnectedState>();
    context.user.alertUser("Call Dropped by "+to_string(from));
}
void TalkingState::handleReceivedCallTalk(const std::string &text)
 {
    context.timer.stopTimer();
    context.user.newCallMessage(text);
    using namespace std::chrono_literals;
    context.timer.startTimer(120s);
}

void TalkingState::handleReceivedCallReject(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void TalkingState::handleTimeout() {
    context.timer.stopTimer();
    context.setState<ConnectedState>();
    context.user.alertUser("User does not respond");
}

void TalkingState::handleUnknownRecipient() {
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void TalkingState::handleCallRequest(common::PhoneNumber from) {
    context.bts.sendCallDropped(from);
}
}