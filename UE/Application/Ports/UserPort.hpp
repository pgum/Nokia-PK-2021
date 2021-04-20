#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    using Selection = unsigned;
    using OptionalSelection = std::pair<bool,Selection>;

    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;

    void showSmsList(std::vector<SMS> smsList) override;
    void ListViewHandler(OptionalSelection index) override;
    void smsListViewHandler(OptionalSelection messageIndex) override;
    void composeSms() override;
    void showSingleSms(SMS sms) override;
    void smsNotification() override;
    void disableSmsNotification() override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
};

}
