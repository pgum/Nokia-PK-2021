#include <future>
#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/IDialMode.hpp"
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
    for(auto i : smsList)
    { 
        std::string messageFrom = "From:" + to_string(i.getPhoneNumberFrom());
        if(!i.getRead())
        {
            messageFrom = messageFrom + "-Not Read!";
        }
        menu.addSelectionListItem(messageFrom,"");

    }
    gui.setAcceptCallback([this,&menu](){
                    OptionalSelection selectedItem = menu.getCurrentItemIndex();
                    Selection selectedItemIndex = selectedItem.second;
                    this->handler->handleSingleSms(selectedItemIndex);
    });
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
    gui.setRejectCallback([this,&composeMode](){composeMode.clearSmsText();showConnected();});
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Call","");
    gui.setAcceptCallback([this,&menu](){
        OptionalSelection selectedItem = menu.getCurrentItemIndex();
        Selection selectedItemIndex = selectedItem.second;
        this->handler->handleMenuList(selectedItemIndex);
    });
    gui.setRejectCallback(nullptr);
}
void UserPort::smsNotification()
{
    gui.showNewSms();
}

void UserPort::showCalling(common::PhoneNumber from)
{

    logger.logInfo("showCalling");
    auto & alertMode = gui.setAlertMode();
    alertMode.setText("call from " + to_string(from));

    gui.setAcceptCallback([this,from]{
        this->handler->handleSendCallAccepted(from);
    });

    gui.setRejectCallback([this,from]{
        this->handler->handleSendCallDropped(from);
    });
}

void UserPort::makeACall(){
    auto &callMenu=gui.setDialMode();
    bool calling= false;

    gui.setAcceptCallback([this,&callMenu,&calling]()mutable{
        common::PhoneNumber enteredPhoneNumber=callMenu.getPhoneNumber();
        logger.logInfo("Calling "+ to_string( enteredPhoneNumber));
        calling=true;
        handler->handleSendCallRequest(enteredPhoneNumber); });

    gui.setRejectCallback([this,&callMenu,calling](){
        common::PhoneNumber enteredPhoneNumber=callMenu.getPhoneNumber();
        logger.logInfo("Dropping Call  "+ to_string( enteredPhoneNumber));
        logger.logInfo(calling);
        if (calling){handler->handleSendCallDropped(enteredPhoneNumber);}
        else {showConnected();}});

}

void UserPort::alertUser(std::string msg) {

//      std::future<void>result=std::async( [this,msg]{ auto &alert=gui.setAlertMode();alert.setText((msg)); });
//      result.wait();
//    using namespace std::chrono_literals;
//    std::this_thread::sleep_for(2s);
    showConnected();
}

}
