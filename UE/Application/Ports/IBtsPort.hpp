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
    virtual void handleUnknownRecipientSMS()=0;
    virtual void handleCallRequest(common::PhoneNumber from)=0;
    virtual void handleReceivedCallAccept(common::PhoneNumber from)=0;
    virtual void handleReceivedCallReject(common::PhoneNumber from)=0;
    virtual void handleReceivedCallTalk(const std::string &text)=0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(SMS sendingSMS) = 0;
    virtual void sendCallAccept(common::PhoneNumber to) =0;
    virtual void sendCallDropped(common::PhoneNumber to) =0;
    virtual void sendCallRequest(common::PhoneNumber to) =0;
    virtual void sendCallTalk(common::PhoneNumber to,const std::string & text)=0;
};

}
