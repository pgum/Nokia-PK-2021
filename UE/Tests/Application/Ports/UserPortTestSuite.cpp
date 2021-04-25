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
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    objectUnderTest.showConnected();
}
TEST_F(UserPortTestSuite,shallHandleHomeMenu)
{
    std::pair<bool,unsigned> testPair;
    testPair.first=true;
    testPair.second=1;

    EXPECT_CALL(handlerMock,handleViewSmsList());

    objectUnderTest.ListViewHandler(testPair);
}
TEST_F(UserPortTestSuite,shallShowSmsList)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));

    std::vector<SMS> testVector;

    SMS sms1("test",PHONE_NUMBER,PHONE_NUMBER,false,true);

    testVector.push_back(sms1);

    objectUnderTest.showSmsList(testVector);
}
TEST_F(UserPortTestSuite,shallHandleSmsList)
{
    EXPECT_CALL(handlerMock,handleSingleSms(_));

    std::pair<bool,unsigned> testPair;
    testPair.first=true;
    testPair.second=1;

    objectUnderTest.smsListViewHandler(testPair);

}
TEST_F(UserPortTestSuite,shallShowSingleSms)
{
    EXPECT_CALL(guiMock, setViewTextMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText(_));
    EXPECT_CALL(guiMock,setRejectCallback);

    SMS sms1("test",PHONE_NUMBER,PHONE_NUMBER,false,true);

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
}
