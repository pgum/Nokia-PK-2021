#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
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


void Application::handleSmsReceived(common::PhoneNumber from, std::string message)
{
    context.state->handleSmsReceived(from, message);
}

void Application::handleSendMessage(const common::PhoneNumber to, const std::string& message)

{
    context.state->handleSendMessage(to, message);
}

void Application::handleCallRequest(common::PhoneNumber from)
{
    context.state->handleCallRequest(from);
}
void Application::handleReceivedCallDrop(common::PhoneNumber phoneNumber)
{
    context.state->handleReceivedCallDrop(phoneNumber);
}

void Application::handleSendCallRequest(const common::PhoneNumber to)
{
    context.state->handleSendCallRequest(to);
}

void Application::handleCallAccepted(const common::PhoneNumber from)
{
    context.state->handleCallAccepted(from);
}

void Application::handleSendCallAccepted(const common::PhoneNumber from)
{
    context.state->handleSendCallAccepted(from);
}

void Application::handleSendCallMessage(const common::PhoneNumber to, const std::string &text)
{
    context.state->handleSendCallMessage(to, text);
}

void Application::handleCallTalk(const common::PhoneNumber from, const std::string &message)
{
    context.state->handleCallTalk(from, message);
}

}
