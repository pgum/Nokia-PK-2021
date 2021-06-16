#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"

namespace ue
{
using namespace ::testing;

class UserPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IUserEventsHandlerMock> handlerMock;
    StrictMock<IUeGuiMock> guiMock;
    StrictMock<IListViewModeMock> listViewModeMock;
    StrictMock<ITextModeMock> textModeMock;
    StrictMock<ISmsComposeModeMock> smsComposeModeMock;
    StrictMock<IDialModeMock> dialModeMock;
    StrictMock<ICallModeMock> callModeMock;
    UserPort objectUnderTest{loggerMock, guiMock, PHONE_NUMBER};

    UserPortTestSuite()
    {
        EXPECT_CALL(guiMock, setTitle(HasSubstr(to_string(PHONE_NUMBER))));
        objectUnderTest.start(handlerMock);
    }
    ~UserPortTestSuite()
    {
        objectUnderTest.stop();
    }
};

TEST_F(UserPortTestSuite, shallStartStop)
{
}

TEST_F(UserPortTestSuite, shallShowNotConnected)
{
    EXPECT_CALL(guiMock, showNotConnected());
    objectUnderTest.showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
    EXPECT_CALL(guiMock, showConnecting());
    objectUnderTest.showConnecting();
}

TEST_F(UserPortTestSuite, shallShowMenuOnConnected)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, "")).Times(3);
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    objectUnderTest.showConnected();
}
TEST_F(UserPortTestSuite,shallShowSmsList)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem("From:1-Not Read!","")).Times(AtLeast(1));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));

    std::vector<SMS> testVector;
    SMS testSmsToShow{"",common::PhoneNumber{1},PHONE_NUMBER,smsRead::NotRead,smsReceived::Received};
    testVector.push_back(testSmsToShow);

    std::unique_ptr<std::vector<SMS>> ptrTestVector = std::make_unique<std::vector<SMS>>(testVector);

    objectUnderTest.showSmsList(std::move(ptrTestVector));
}
TEST_F(UserPortTestSuite,shallHandleSmsList)
{
    EXPECT_CALL(handlerMock,handleSingleSms(1));

    std::pair<bool,unsigned> testPair;
    testPair.first=true;
    testPair.second=1;

    objectUnderTest.smsListViewHandler(testPair);

}
TEST_F(UserPortTestSuite,shallShowSingleSms)
{
    EXPECT_CALL(guiMock, setViewTextMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText("test"));
    EXPECT_CALL(guiMock,setRejectCallback);

    SMS sms1("test",PHONE_NUMBER,PHONE_NUMBER,smsRead::NotRead,smsReceived::Received);

    objectUnderTest.showSingleSms(sms1);
}
TEST_F(UserPortTestSuite,shallSetComposeSmsMode)
{
    EXPECT_CALL(guiMock, setSmsComposeMode()).WillOnce(ReturnRef(smsComposeModeMock));
    EXPECT_CALL(smsComposeModeMock,clearSmsText());
    EXPECT_CALL(guiMock,setRejectCallback(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));

    objectUnderTest.composeSms();
}
TEST_F(UserPortTestSuite,shallShowNewSms)
{
    EXPECT_CALL(guiMock,showNewSms);

    objectUnderTest.smsNotification();
}

TEST_F(UserPortTestSuite,shallMakeACall)
{
    EXPECT_CALL(guiMock,setDialMode()).WillOnce(ReturnRef(dialModeMock));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));

    objectUnderTest.makeACall();
}

TEST_F(UserPortTestSuite,shallShowCalling)
{
    EXPECT_CALL(guiMock,setAlertMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));

    objectUnderTest.showCalling(PHONE_NUMBER);
}

TEST_F(UserPortTestSuite,shallAlertUser)
{
    EXPECT_CALL(guiMock,setAlertMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    objectUnderTest.alertUser("to jest test");
}

TEST_F(UserPortTestSuite,shallSetCallModeAndNewCallMessage)
{
    EXPECT_CALL(guiMock,setCallMode()).WillOnce(ReturnRef(callModeMock));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    objectUnderTest.setCallMode(PHONE_NUMBER);

    EXPECT_CALL(callModeMock,clearIncomingText());
    EXPECT_CALL(callModeMock,appendIncomingText(_));
    objectUnderTest.newCallMessage("to jest test");
}

TEST_F(UserPortTestSuite,shallWaitingForCallRespond)
{
    EXPECT_CALL(guiMock,setAlertMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText(_));
    objectUnderTest.waitingForCallRespond();
}

}
