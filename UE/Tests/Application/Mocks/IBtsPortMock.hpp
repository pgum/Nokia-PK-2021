#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleNewSms,(SMS sms),(final));
    MOCK_METHOD(void, handleUnknownRecipient,(),(final));
    MOCK_METHOD(void, handleUnknownRecipientSMS,(),(final));
    MOCK_METHOD(void,handleCallRequest,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,handleReceivedCallAccept,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,handleReceivedCallReject,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,handleReceivedCallTalk,(const std::string &text),(final));

};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;
    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void,sendSms,(SMS sendingSMS),(final));
    MOCK_METHOD(void,sendCallAccept,(common::PhoneNumber to),(final));
    MOCK_METHOD(void,sendCallDropped,(common::PhoneNumber to),(final));
    MOCK_METHOD(void,sendCallRequest,(common::PhoneNumber to),(final));
    MOCK_METHOD(void,sendCallTalk,(common::PhoneNumber to,const std::string & text),(final));
};

}
