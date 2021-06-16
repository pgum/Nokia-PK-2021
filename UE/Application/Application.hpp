#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer,
                ISmsDb &smsDb);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;//<--C T

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleCallRequest(common::PhoneNumber from) override;//T<--
    void handleReceivedCallAccept(common::PhoneNumber from) override;
    void handleReceivedCallReject(common::PhoneNumber from) override;//<--T
    void handleReceivedCallTalk(const std::string &text)override;//<-T
    void handleUnknownRecipientSMS()override;
    void handleUnknownRecipient() override;//<--T
    //IUserEventsHandler
    void handleViewSmsList() override;
    void handleSingleSms(int messageIndex) override;
    void handleSendSms(SMS sendingSMS) override;
    void handleNewSms(SMS sms) override;
    void handleMenuList(unsigned selectionIndex) override;

    void handleSendCallAccepted(common::PhoneNumber from) override;
    void handleSendCallDropped(common::PhoneNumber from) override;//T
    void handleSendCallRequest(common::PhoneNumber to) override;
    void handleSendCallTalk(common::PhoneNumber to, const std::string &msg) override;//<--T
private:
    Context context;
    common::PrefixedLogger logger;

};

}
