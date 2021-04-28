#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Mocks/ISmsDBMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Messages/BtsId.hpp"
#include "Ports/SMS.hpp"
#include <memory>

namespace ue
{
using namespace ::testing;
using namespace std::chrono_literals;

class ApplicationTestSuite : public Test
{
protected:
    const common::BtsId BTS_ID{42};
    const common::PhoneNumber PHONE_NUMBER{112};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;
    StrictMock<ISmsDBMock> smsDbMock;

    Expectation expectShowNotConnected = EXPECT_CALL(userPortMock, showNotConnected());
    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock,
                                smsDbMock
                               };
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{};

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
{
    ApplicationConnectingTestSuite();
    void doConnecting();
};

ApplicationConnectingTestSuite::ApplicationConnectingTestSuite()
{
    doConnecting();
}

void ApplicationConnectingTestSuite::doConnecting()
{
    EXPECT_CALL(userPortMock, showConnecting());
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, startTimer(500ms));
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib)
{
    // everything in constructor
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachReject)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachTimeout)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleTimeout();
}

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
    void doConnected();
};

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    doConnected();
}

void ApplicationConnectedTestSuite::doConnected()
{
    EXPECT_CALL(userPortMock, showConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationConnectedTestSuite, shallShowConnectedOnAttachAccept)
{
    // see test-suite constructor
}

TEST_F(ApplicationConnectedTestSuite, shallShowNotConnectedOnDisconnectFromBts)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallReattach)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();

    doConnecting();
    doConnected();
}
TEST_F(ApplicationConnectedTestSuite, shallHandleViewSmsList)
{
    std::vector<SMS> smsVector;
    EXPECT_CALL(smsDbMock,getAllReceivedSms()).WillOnce(Return (smsVector));
    EXPECT_CALL(userPortMock,showSmsList(smsVector));
    objectUnderTest.handleViewSmsList();
}
TEST_F(ApplicationConnectedTestSuite, shallHandleSingleSms)
{
    SMS testSms;
    int testMessageIndex;
    EXPECT_CALL(smsDbMock,getReceivedSms(testMessageIndex)).WillOnce(Return (testSms));
    EXPECT_CALL(userPortMock,showSingleSms(testSms));
    objectUnderTest.handleSingleSms(testMessageIndex);
}
TEST_F(ApplicationConnectedTestSuite,shallHandleSendSms)
{
    SMS testSendingSms;
    EXPECT_CALL(smsDbMock,addSendSms(_));
    EXPECT_CALL(btsPortMock,sendSms(_));
    objectUnderTest.handleSendSms(testSendingSms);
}
TEST_F(ApplicationConnectedTestSuite,shallHandleNewSms)
{
    SMS testSms;
    EXPECT_CALL(smsDbMock,addReceivedSms(testSms));
    EXPECT_CALL(userPortMock,smsNotification());
    objectUnderTest.handleNewSms(testSms);
}
TEST_F(ApplicationConnectedTestSuite,shallHandleUnknownRecipient)
{
    EXPECT_CALL(smsDbMock,unknownRecipientSms());
    objectUnderTest.handleUnknownRecipient();
}
}
