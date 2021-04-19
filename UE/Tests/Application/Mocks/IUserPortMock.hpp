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
    MOCK_METHOD(void,showSmsList,(std::vector<SMS> smsList),(final));
    MOCK_METHOD(void,ListViewHandler,(OptionalSelection index),(final));
    MOCK_METHOD(void,smsListViewHandler,(OptionalSelection messageIndex),(final));
    MOCK_METHOD(void,composeSms,(),(final));
    //MOCK_METHOD(void,sendSMS,(),(final));
    MOCK_METHOD(void,showSingleSms,(SMS sms),(final));
};

}
