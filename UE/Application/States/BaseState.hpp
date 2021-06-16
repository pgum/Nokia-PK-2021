#pragma once

#include <Messages/MessageId.hpp>
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:


    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleReceivedCallAccept(common::PhoneNumber from) override;
    void handleReceivedCallReject(common::PhoneNumber from) override;
    void handleReceivedCallTalk(const std::string &text) override;
    void handleUnknownRecipientSMS()override;
    //IUserEventsHandler
    void handleViewSmsList() override;
    void handleSingleSms(int messageIndex) override;
    void handleSendSms(SMS sendingSMS) override;
    void handleNewSms(SMS sms) override;
    void handleUnknownRecipient() override;
    void handleMenuList(unsigned int selectionIndex) override;
    void handleCallRequest(common::PhoneNumber from) override;//<---do Ibtsevent
    void handleSendCallAccepted(common::PhoneNumber from) override;
    void handleSendCallDropped(common::PhoneNumber from) override;
    void handleSendCallRequest(common::PhoneNumber to) override;
    void handleSendCallTalk(common::PhoneNumber to, const std::string &msg) override;
protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
