#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "SmsDb.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    using Selection = unsigned;
    using OptionalSelection = std::pair<bool,Selection>;

    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber,ISmsDb& smsdb);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;

    void showSmsList() override;
    void ListViewHandler(OptionalSelection index) override;
    void smsListViewHandler(OptionalSelection messageIndex) override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    ISmsDb& smsdb;
};

}
