#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

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


void ConnectedState::handleSmsReceived(common::PhoneNumber from,
                                       std::string text)
{
    Sms incomingSms(from,text);
    incomingSms.read = false;
    context.db.insert(incomingSms);
    context.user.showNewSms();

void ConnectedState::handleSendMessage(common::PhoneNumber from, std::string message)
{
    context.bts.sendMessage(from, message);
}

}
