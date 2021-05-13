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
    //Sms incomingSms(from,text);
    //incomingSms.read = false;
    //context.db.insert(incomingSms);
    context.user.showSmsReceived();
}

void ConnectedState::handleSendMessage(const common::PhoneNumber to, const std::string& message)
{
    context.bts.sendMessage(to, message);
}

}
