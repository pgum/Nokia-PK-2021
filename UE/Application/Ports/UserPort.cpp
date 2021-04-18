#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber,ISmsDb &smsdb)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber),
      smsdb(smsdb)
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

void UserPort::smsListViewHandler(OptionalSelection messageIndex)
{
    SMS currentSms = this->smsdb.getSMS(messageIndex.second);
    IUeGui::ITextMode& messageView = gui.setViewTextMode();
    currentSms.setRead();
    messageView.setText(currentSms.getMessage());
}

void UserPort::showSmsList()
{
    std::vector<SMS> smsList = this->smsdb.getAllSms();
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    int smsIndex=0;
    for(std::vector<SMS>::iterator i=smsList.begin();
            i!=smsList.end();
            i++
        ){
        SMS currentSms = smsdb.getSMS(smsIndex);
        std::string messageFrom = "From: " + to_string(currentSms.getPhoneNumber());
        menu.addSelectionListItem(messageFrom,"");
        smsIndex++;
    }
    gui.setAcceptCallback([&](){smsListViewHandler(menu.getCurrentItemIndex());});
}

void UserPort::ListViewHandler(OptionalSelection index)
{
    if(index.second==1)showSmsList();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    gui.setAcceptCallback([&](){ListViewHandler(menu.getCurrentItemIndex());});
}

}
