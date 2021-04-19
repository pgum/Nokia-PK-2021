#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"

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

void UserPort::showSingleSms(SMS currentSms)
{
    IUeGui::ITextMode& messageView = gui.setViewTextMode();
    currentSms.setRead();
    messageView.setText(currentSms.getMessage());
    gui.setRejectCallback([*this](){this->handler->handleViewSmsList();});
}

void UserPort::smsListViewHandler(OptionalSelection messageIndex)
{
    this->handler->handleSingleSms(messageIndex.second);
}

void UserPort::showSmsList(std::vector<SMS> smsList)
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for(std::vector<SMS>::iterator i=smsList.begin();
            i!=smsList.end();
            i++
        ){
        std::string messageFrom = "From: " + to_string(i->getPhoneNumber());
        menu.addSelectionListItem(messageFrom,"");
    }
    gui.setAcceptCallback([&](){smsListViewHandler(menu.getCurrentItemIndex());});
    gui.setRejectCallback([this](){showConnected();});
}

void UserPort::composeSms(){
    IUeGui::ISmsComposeMode &composeMode = gui.setSmsComposeMode();
    gui.setAcceptCallback([&](){handler->handleSendSms(phoneNumber,composeMode.getPhoneNumber(),composeMode.getSmsText());
        composeMode.clearSmsText();
        showConnected();});
    gui.setRejectCallback([&](){composeMode.clearSmsText();showConnected();});
}

void UserPort::ListViewHandler(OptionalSelection index)
{
    if(index.second==0)composeSms();
    else if(index.second==1)this->handler->handleViewSmsList();
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
