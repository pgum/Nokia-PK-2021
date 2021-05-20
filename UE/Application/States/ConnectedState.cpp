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
    context.user.showNewSms();
}
void ConnectedState::handleSendMessage(const common::PhoneNumber to, const std::string& message)
{
    //Sms incomingSms(from,text);
    //incomingSms.read = false;
    //context.db.insert(incomingSms);
    context.user.showSmsReceived();
}

void ConnectedState::handleCallRequest(common::PhoneNumber from)
{
    logger.logInfo("Received call request from ", from);
}

void ConnectedState::handleReceivedCallDrop(common::PhoneNumber recipient)
{
    context.logger.logDebug("Received Call drop from ", recipient);
}

void ConnectedState::handleSendCallRequest(const common::PhoneNumber to)
{
    context.bts.sendCallRequest(to);
}

void ConnectedState::handleCallAccepted(const common::PhoneNumber from)
{
    context.user.setConversationMode(from);
}

}
