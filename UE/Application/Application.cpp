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
void Application::handleViewSmsList()
{
    std::vector<SMS> smsList = context.smsDb.getAllReceivedSms();
    this->context.user.showSmsList(smsList);
}
void Application::handleSingleSms(int messageIndex)
{
    SMS currentSms = context.smsDb.getReceivedSMS(messageIndex);
    //if(context.smsDb.checkIfAllReceivedRead())context.user.disableSmsNotification();
    context.user.showSingleSms(currentSms);
}
void Application::handleSendSms(common::PhoneNumber from, common::PhoneNumber to, std::string text)
{
    SMS sendingSms = SMS(text,from,to,true,true);
    context.smsDb.addSendSMS(sendingSms);
    context.bts.sendSms(from,to,text);
}
void Application::handleNewSms(SMS sms)
{
    context.smsDb.addReceivedSMS(sms);
    context.user.smsNotification();
}
void Application::handleUnknownRecipient()
{
    context.smsDb.unknownRecipientSMS();
}
}
