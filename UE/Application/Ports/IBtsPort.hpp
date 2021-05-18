#pragma once

#include <Messages/MessageId.hpp>
#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Ports/SMS.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleDisconnected() = 0;
    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject()=0;
    virtual void handleNewSms(SMS newSms) = 0;
    virtual void handleUnknownRecipient() = 0;
    virtual void handleCallRequest(common::PhoneNumber from)=0;


};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(SMS sendingSMS) = 0;
    virtual void sendCallRespond(common::PhoneNumber from, common::PhoneNumber to, common::MessageId id)=0;
    virtual void sendCallRequest(common::PhoneNumber from, common::PhoneNumber to)=0;
};

}
