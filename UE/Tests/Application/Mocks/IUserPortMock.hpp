#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;
    MOCK_METHOD(void,handleViewSmsList,(),(final));
    MOCK_METHOD(void,handleSingleSms,(int messageIndex),(final));
    MOCK_METHOD(void,handleSendSms,(SMS sendingSMS),(final));
    MOCK_METHOD(void,handleMenuList,(unsigned int selectionIndex),(final));
    MOCK_METHOD(void,handleSendCallAccepted,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,handleSendCallDropped,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,handleSendCallRequest,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,handleSendCallTalk,(common::PhoneNumber to, const std::string &msg),(final));
};

class IUserPortMock : public IUserPort
{
public:
    using Selection = unsigned;
    using OptionalSelection = std::pair<bool,Selection>;

    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void,showSmsList,(std::unique_ptr<std::vector<SMS>> smsList),(final));
    MOCK_METHOD(void,smsListViewHandler,(OptionalSelection messageIndex),(final));
    MOCK_METHOD(void,composeSms,(),(final));
    MOCK_METHOD(void,showSingleSms,(SMS sms),(final));
    MOCK_METHOD(void,smsNotification,(),(final));
    MOCK_METHOD(void,showCalling,(common::PhoneNumber from),(final));
    MOCK_METHOD(void,makeACall,(),(final));
    MOCK_METHOD(void,alertUser,(std::string msg),(final));
    MOCK_METHOD(void,setCallMode,(common::PhoneNumber partnerPhoneNumber),(final));
    MOCK_METHOD(void,waitingForCallRespond,(),(final));
    MOCK_METHOD(void,newCallMessage,(const std::string &text),(final));

};

}
