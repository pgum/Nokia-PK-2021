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
    for(std::vector<SMS>::iterator i=smsList.begin();i!=smsList.end();i++)
    {
        if(i->getPhoneNumberTo()==phoneNumber)
        {
            std::string messageFrom = "From:" + to_string(i->getPhoneNumberFrom());
            if(!i->getRead())
            {
                messageFrom = messageFrom + "-Not Read!";
            }
            menu.addSelectionListItem(messageFrom,"");
        }

    }
    gui.setAcceptCallback([&](){smsListViewHandler(menu.getCurrentItemIndex());});
    gui.setRejectCallback([this](){showConnected();});
}

void UserPort::composeSms(){
    IUeGui::ISmsComposeMode &composeMode = gui.setSmsComposeMode();
    composeMode.clearSmsText();
    gui.setAcceptCallback([&composeMode,this](){
                    SMS sendingSMS{composeMode.getSmsText(),phoneNumber,composeMode.getPhoneNumber(),true,true};
                    handler->handleSendSms(sendingSMS);
                    composeMode.clearSmsText();
                    showConnected();});
    gui.setRejectCallback([&](){composeMode.clearSmsText();showConnected();});
}

void UserPort::showConnected()
{


    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    gui.setAcceptCallback([this,&menu](){
                    OptionalSelection selectedItem = menu.getCurrentItemIndex();
                    Selection selectedItemIndex = selectedItem.second;
                    this->handler->handleMenuList(selectedItemIndex);
    });
}
void UserPort::smsNotification()
{
    gui.showNewSms();
}
}
