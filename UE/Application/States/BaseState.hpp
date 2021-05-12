#pragma once

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

    //IUserEventsHandler
    void handleViewSmsList() override;
    void handleSingleSms(int messageIndex) override;
    void handleSendSms(SMS sendingSMS) override;
    void handleNewSms(SMS sms) override;
    void handleUnknownRecipient() override;
    void handleMenuList(unsigned int selectionIndex) override;
    void handleCallRequest(common::PhoneNumber from) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
