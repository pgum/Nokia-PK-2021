#pragma once
#include <utility>
#include <vector>
#include "SMS.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleViewSmsList() = 0;
    virtual void handleSingleSms(int messageIndex) = 0;
};

class IUserPort
{
public:
    using Selection = unsigned;
    using OptionalSelection = std::pair<bool,Selection>;

    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;

    virtual void showSmsList(std::vector<SMS> smsList) = 0;
    virtual void ListViewHandler(OptionalSelection index) = 0;
    virtual void smsListViewHandler(OptionalSelection messageIndex) = 0;
    virtual void composeSms() = 0;
    virtual void showSingleSms(SMS sms) = 0;
};

}
