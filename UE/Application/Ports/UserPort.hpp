#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include <memory>
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
    void alertUser(std::string msg) override;
    void showSmsList(std::unique_ptr<std::vector<SMS>> smsList) override;
    void smsListViewHandler(OptionalSelection messageIndex) override;
    void composeSms() override;
    void showSingleSms(SMS sms) override;
    void smsNotification() override;
    void showCalling(common::PhoneNumber from) override;
    void makeACall() override;
    void setCallMode(common::PhoneNumber partnerPhoneNumber) override;
    void waitingForCallRespond() override;
    void newCallMessage(const std::string &text) override;
private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    IUeGui::ICallMode *callMode= nullptr;
};

}
