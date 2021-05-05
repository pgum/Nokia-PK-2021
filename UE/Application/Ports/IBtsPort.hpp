#pragma once

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
    virtual void handleAttachReject() = 0;

    virtual void handleNewSms(SMS newSms) = 0;
    virtual void handleUnknownRecipient() = 0;
    /*
    virtual void sendCallRequestAccepted(common::PhoneNumber) = 0;
    virtual void sendCallRequestRejected(common::PhoneNumber) = 0;
     */
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(SMS sendingSMS) = 0;
};

}
