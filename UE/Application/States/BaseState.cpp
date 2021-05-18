#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleDisconnected()
{
    logger.logError("Uexpected: handleDisconnected");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Uexpected: handleAttachAccept");
}

void BaseState::handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}
void BaseState::handleViewSmsList()
{
    logger.logError("Unexpected: handleViewSms");
}
void BaseState::handleSingleSms(int messageIndex)
{
    logger.logError("Unexpected: handleSingleSms");
}
void BaseState::handleSendSms(SMS sendingSMS)
{
    logger.logError("Unexpected: handleSendSms");
}
void BaseState::handleNewSms(SMS newSms)
{
    logger.logError("Unexpected: handleNewSms");
}
void BaseState::handleUnknownRecipient()
{
    logger.logError("Unexpected: handleUnknownRecipient");
}
void BaseState::handleMenuList(unsigned int selectionIndex)
{
    logger.logError("Unexpected: handleMenuList");
}

void BaseState::handleCallRequest(common::PhoneNumber from)
{
    logger.logError("Unexpected: handleCallRequest");
}
void BaseState::handleAcceptCall(common::PhoneNumber from) {
    logger.logError("Unexpected: handleAcceptCall");
}
void BaseState::handleRejectCall(common::PhoneNumber from) {
    logger.logError("Unexpected: handleRejectCall");
}

void BaseState::handleSendCallRequest(common::PhoneNumber to) {
    logger.logError("Unexpected : handleSendCallRequest ");
}

}
