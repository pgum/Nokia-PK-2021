#pragma once

#include "IUeGui.hpp"


namespace ue
{
enum class View {
    Status,
    HomeMenu,
    NewSms,
    SmsList,
    SmsSent,
    SmsReceived,
    SmsView,
    SentSmsView,
    IncomingCall,
    OutgoingCall,
    NewCall,
    Call
};

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showNewSms() = 0;
    virtual void showSmsList() = 0;
    virtual void showMenu() = 0;
    virtual void showSms(int id) = 0;
    virtual void showComposeSmsMode() = 0;
    virtual void showSmsReceived() = 0;
    virtual void showSentSMSList() = 0;
    virtual void showSentSMS(int id) = 0;
    virtual void setCurMode(View curView, IUeGui::BaseMode* mode) = 0;
};

}
