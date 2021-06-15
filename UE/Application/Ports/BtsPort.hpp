#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BtsPort : public IBtsPort
{
public:
    BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
    void start(IBtsEventsHandler& handler);
    void stop();

    void sendAttachRequest(common::BtsId) override;

    void sendSms(SMS sendingSMS) override;
    void sendCallAccept(common::PhoneNumber to) override;
    void sendCallDropped(common::PhoneNumber to) override;
    void sendCallRequest(common::PhoneNumber to) override;
    void sendCallTalk(common::PhoneNumber to,const std::string & text) override;
private:
    void handleDisconnected();
    void handleMessage(BinaryMessage msg);

    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;

    IBtsEventsHandler* handler = nullptr;
};

}
