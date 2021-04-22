#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
}

void UserPort::showSmsReceived()
{
    gui.showSmsReceived();
}

void UserPort::showSms(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db.get(id);
    std::string text="From: "+to_string(sms->from)+"\n\n"+sms->message;
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db.getAll())
        if(sms.read==false){allRead=false;break;}
    if(allRead==true)showSmsReceived();
    setCurrentMode(View::SmsView, &menu);
}

void UserPort::showSentSMS(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db_w.get(id);
    std::string text="To: "+to_string(sms->from)+"\n\n"+sms->message;
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db_w.getAll())
        if(sms.read==false){allRead=false;break;}
    if(allRead==true)showSmsReceived();
    setCurrentMode(View::SentSmsView, &menu);
}

}
