#include <future>
#include <UeGui/ICallMode.hpp>
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
    messageView.setText(currentSms.message);
    gui.setRejectCallback([this](){this->handler->handleViewSmsList();});
}

void UserPort::smsListViewHandler(OptionalSelection messageIndex)
{
    this->handler->handleSingleSms(messageIndex.second);
}

void UserPort::showSmsList(std::unique_ptr<std::vector<SMS>> smsList)
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for(auto&& sms : *smsList)
    { 
        std::string messageFrom = "From:" + to_string(sms.from);
        if(sms.read==smsRead::NotRead)
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
                    SMS sendingSMS{composeMode.getSmsText(),
                                   phoneNumber,
                                   composeMode.getPhoneNumber(),
                                   smsRead::Read,
                                   smsReceived::Received};
                    handler->handleSendSms(sendingSMS);
                    composeMode.clearSmsText();
                    showConnected();});
    gui.setRejectCallback([this,&composeMode](){composeMode.clearSmsText();showConnected();});
}

void UserPort::showConnected()
{
    callMode= nullptr;
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
    auto &dialMenu=gui.setDialMode();

    gui.setAcceptCallback([this,&dialMenu](){
        common::PhoneNumber enteredPhoneNumber=dialMenu.getPhoneNumber();
        logger.logInfo("Calling "+ to_string( enteredPhoneNumber));
        handler->handleSendCallRequest(enteredPhoneNumber);

        gui.setRejectCallback([this,&dialMenu]{
            common::PhoneNumber enteredPhoneNumber=dialMenu.getPhoneNumber();
            logger.logInfo("Sending droped call to "+ to_string( enteredPhoneNumber));
            handler->handleSendCallDropped(enteredPhoneNumber);
        });
    });

    gui.setRejectCallback([this](){showConnected();});

}

void UserPort::setCallMode(common::PhoneNumber partnerPhoneNumber) {
    callMode=&gui.setCallMode();

    gui.setAcceptCallback([=](){
        auto text=callMode->getOutgoingText();
        if(!(text.empty())){
            logger.logInfo("setCallMode  "+to_string(partnerPhoneNumber));
            handler->handleSendCallTalk(partnerPhoneNumber,text);
            callMode->clearOutgoingText();
        }
    });
    gui.setRejectCallback([=](){handler->handleSendCallDropped(partnerPhoneNumber);});
}

void UserPort::newCallMessage(const std::string &text) {
    callMode->clearIncomingText();
    callMode->appendIncomingText(text);
}

void UserPort::waitingForCallRespond() {
    auto &alert=gui.setAlertMode();
    alert.setText("Calling ...");
}


void UserPort::alertUser(std::string msg) {

    auto &alert=gui.setAlertMode();
    alert.setText((msg));
    gui.setAcceptCallback([=](){showConnected();});
    gui.setRejectCallback([=](){showConnected();});
}

}
