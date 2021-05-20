
#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue {

    Application::Application(common::PhoneNumber phoneNumber,
                             common::ILogger &iLogger,
                             IBtsPort &bts,
                             IUserPort &user,
                             ITimerPort &timer,
                             ISmsDb &smsDb)
            : context{iLogger, bts, user, timer, smsDb},
              logger(iLogger, "[APP] ") {
        logger.logInfo("Started");
        context.setState<NotConnectedState>();
    }

    Application::~Application() {
        logger.logInfo("Stopped");
    }

    void Application::handleTimeout() {
        context.state->handleTimeout();
    }

    void Application::handleDisconnected() {
        context.state->handleDisconnected();
    }

    void Application::handleSib(common::BtsId btsId) {
        context.state->handleSib(btsId);
    }

    void Application::handleAttachAccept() {
        context.state->handleAttachAccept();
    }

    void Application::handleAttachReject() {
        context.state->handleAttachReject();
    }

    void Application::handleMenuList(unsigned int selectionIndex) {

        switch(selectionIndex){
            case 0:
                context.user.composeSms();
                break;
            case 1:
                handleViewSmsList();
                break;
            case 2:
                context.user.makeACall();
                break;

        }
    }

    void Application::handleViewSmsList() {
        std::vector<SMS> smsList = context.smsDb.getAllReceivedSms();
        context.user.showSmsList(smsList);
    }

    void Application::handleSingleSms(int messageIndex) {
        SMS currentSms = context.smsDb.getReceivedSms(messageIndex);
        context.user.showSingleSms(currentSms);
    }

    void Application::handleSendSms(SMS sendingSms) {
        context.smsDb.addSendSms(sendingSms);
        context.bts.sendSms(sendingSms);
    }

    void Application::handleNewSms(SMS sms) {
        context.smsDb.addReceivedSms(sms);
        context.user.smsNotification();
    }

    void Application::handleUnknownRecipient() {
        context.smsDb.unknownRecipientSms();
    }
    void Application::handleCallRequest(common::PhoneNumber from){
        context.state->handleCallRequest(from);
    }
    void Application::handleSendCallAccepted(common::PhoneNumber from){
        context.state->handleSendCallAccepted(from);
    }
    void Application::handleSendCallDropped(common::PhoneNumber from){
        context.state->handleSendCallDropped(from);
    }
    void Application::handleSendCallRequest(common::PhoneNumber to){
        context.state->handleSendCallRequest(to);
    }
    void Application::handleReceivedCallAccept(common::PhoneNumber from) {
        context.state->handleReceivedCallAccept(from);
    }
    void Application::handleReceivedCallReject(common::PhoneNumber from) {
        context.state->handleReceivedCallReject(from);
    }
}

