#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer,
                         ISmsDb &smsDb)
    : context{iLogger, bts, user, timer,smsDb},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}

void Application::handleDisconnected()
{
    context.state->handleDisconnected();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}
void Application::handleMenuList(unsigned int selectionIndex)
{
    if(selectionIndex == 0)
    {
        context.user.composeSms();
    }
    else
    {
        handleViewSmsList();
    }
}
void Application::handleViewSmsList()
{
    context.user.showSmsList(context.smsDb.getAllReceivedSms());
}
void Application::handleSingleSms(int messageIndex)
{
    context.user.showSingleSms(context.smsDb.getReceivedSms(messageIndex));
}
void Application::handleSendSms(SMS sendingSms)
{
    context.smsDb.addSendSms(sendingSms);
    context.bts.sendSms(sendingSms);
}
void Application::handleNewSms(SMS sms)
{
    context.smsDb.addReceivedSms(sms);
    context.user.smsNotification();
}
void Application::handleUnknownRecipient()
{
    context.smsDb.unknownRecipientSms();
}
}
