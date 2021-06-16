#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"
#include "Ports/SMS.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback([this]() {handleDisconnected();});
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleDisconnected()
{
    handler->handleDisconnected();
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
        case common::MessageId::Sib:
        {
            auto btsId = reader.readBtsId();
            handler->handleSib(btsId);
            break;
        }
        case common::MessageId::AttachResponse:
        {
            bool accept = reader.readNumber<std::uint8_t>() != 0u;
            if (accept)
                handler->handleAttachAccept();
            else
                handler->handleAttachReject();
            break;
        }
        case common::MessageId::Sms:
        {
            SMS newSms(reader.readRemainingText(),from,to,smsRead::NotRead,smsReceived::Received);
            handler->handleNewSms(newSms);
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            switch (reader.readMessageHeader().messageId) {
                case common::MessageId::Sms:
                    handler->handleUnknownRecipientSMS();
                    break;
                case common::MessageId::CallRequest:
                    handler->handleUnknownRecipient();
                    break;
            }
            break;
        }
        case common::MessageId::CallRequest:
        {
            handler->handleCallRequest(from);
            break;
        }
        case common::MessageId::CallAccepted:
        {
            handler->handleReceivedCallAccept(from);
            break;
        }
        case common::MessageId::CallDropped:
        {
            handler->handleReceivedCallReject(from);
            break;
        }
        case common::MessageId::CallTalk:
        {
            handler->handleReceivedCallTalk(reader.readRemainingText());
            break;
        }
        default:
            logger.logError("unknow message: ", msgId, ", from: ", from," to: ",to);
        }
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}


void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());


}
void BtsPort::sendSms(SMS sendingSMS)
{
    common::OutgoingMessage msg{common::MessageId::Sms,
                               sendingSMS.from,
                               sendingSMS.to};
    msg.writeText(sendingSMS.message);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallAccept(common::PhoneNumber to) {
    logger.logInfo("sending CallAccepted"+to_string(to));
    common::OutgoingMessage msg{common::MessageId::CallAccepted,phoneNumber,to};
    transport.sendMessage(msg.getMessage());
}
void BtsPort::sendCallDropped(common::PhoneNumber to) {
    logger.logInfo("sending CallDropped"+to_string(to));
    common::OutgoingMessage msg{common::MessageId::CallDropped,phoneNumber,to};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallRequest(common::PhoneNumber to) {
    common::OutgoingMessage msg{common::MessageId::CallRequest,phoneNumber,to};
    transport.sendMessage(msg.getMessage());
}
void BtsPort::sendCallTalk(common::PhoneNumber to, const std::string &text) {
    logger.logInfo("numer "+to_string(to)+"  "+text);
    common::OutgoingMessage msg{common::MessageId::CallTalk,phoneNumber,to};
    msg.writeText(text);
    transport.sendMessage(msg.getMessage());
}
}
