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
struct ApplicationTalkingTestSuite :ApplicationConnectedTestSuite
{
    ApplicationTalkingTestSuite();
    void setTalkingState();
};

ApplicationTalkingTestSuite::ApplicationTalkingTestSuite()
{
    setTalkingState();
}

void ApplicationTalkingTestSuite::setTalkingState()
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,setCallMode(_));
    EXPECT_CALL(timerPortMock,startTimer(_));
    objectUnderTest.handleReceivedCallAccept(PHONE_NUMBER);
}

TEST_F(ApplicationTalkingTestSuite,shallShowCallModeOnRecivedCallAccept)
{
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
    EXPECT_CALL(smsDbMock,getAllReceivedSms()).WillOnce(Return(ByMove(std::make_unique<std::vector<SMS>>())));
    EXPECT_CALL(userPortMock,showSmsList(_));
    objectUnderTest.handleViewSmsList();
}

TEST_F(ApplicationConnectedTestSuite, shallHandleSingleSms)
{
    SMS testSms;
    int testMessageIndex = 0;
    EXPECT_CALL(smsDbMock,getReceivedSms(testMessageIndex)).WillOnce(Return (testSms));
    EXPECT_CALL(userPortMock,showSingleSms(testSms));
    objectUnderTest.handleSingleSms(testMessageIndex);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleSendSms)
{
    SMS testSendingSms;
    EXPECT_CALL(smsDbMock,addSendSms(testSendingSms));
    EXPECT_CALL(btsPortMock,sendSms(testSendingSms));
    objectUnderTest.handleSendSms(testSendingSms);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleNewSms)
{
    SMS testSms;
    EXPECT_CALL(smsDbMock,addReceivedSms(testSms));
    EXPECT_CALL(userPortMock,smsNotification());
    objectUnderTest.handleNewSms(testSms);
}

TEST_F(ApplicationConnectedTestSuite,handleUnknownRecipientSMS)
{
    EXPECT_CALL(smsDbMock,unknownRecipientSms());
    objectUnderTest.handleUnknownRecipientSMS();
}

TEST_F(ApplicationConnectedTestSuite,handleUnknownRecipientOnConnected)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,alertUser(_));
    objectUnderTest.handleUnknownRecipient();
}

TEST_F(ApplicationConnectedTestSuite,shallHandleCallRequestOnConnected)
{
    auto sender=common::PhoneNumber{123};
    EXPECT_CALL(userPortMock,showCalling(_));
    objectUnderTest.handleCallRequest(sender);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleReceivedCallAccept)
{

    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,setCallMode(_));
    EXPECT_CALL(timerPortMock,startTimer(_));
    objectUnderTest.handleReceivedCallAccept(PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleReceivedCallRejectOnConnected)
{

    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,alertUser(_));
    objectUnderTest.handleReceivedCallReject(PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleSendCallAccepted)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(btsPortMock,sendCallAccept(_));
    EXPECT_CALL(userPortMock,setCallMode(_));
    EXPECT_CALL(timerPortMock,startTimer(_));
    objectUnderTest.handleSendCallAccepted(PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleSendCallDroppedOnConnected)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(btsPortMock,sendCallDropped(_));
    EXPECT_CALL(userPortMock,showConnected());

    objectUnderTest.handleSendCallDropped(PHONE_NUMBER);
}
TEST_F(ApplicationConnectedTestSuite,shallHandleSendCallRequest)
{
    EXPECT_CALL(btsPortMock,sendCallRequest(_));
    EXPECT_CALL(userPortMock,waitingForCallRespond());
    EXPECT_CALL(timerPortMock,startTimer(_));

    objectUnderTest.handleSendCallRequest(PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleTimeoutOnConnected)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,alertUser(_));
    objectUnderTest.handleTimeout();
}

TEST_F(ApplicationTalkingTestSuite,shallHandleSendCallTalk){
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(btsPortMock,sendCallTalk(_,_));
    EXPECT_CALL(timerPortMock,startTimer(_));
    objectUnderTest.handleSendCallTalk(PHONE_NUMBER,"to tylko test");
}

TEST_F(ApplicationTalkingTestSuite,shallHandleSendCallDroppedOnTalkingState){
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(btsPortMock,sendCallDropped(_));
    EXPECT_CALL(userPortMock,showConnected());
    EXPECT_CALL(userPortMock,alertUser(_));
    objectUnderTest.handleSendCallDropped(PHONE_NUMBER);
}
TEST_F(ApplicationTalkingTestSuite,shallhandleReceivedCallTalk){
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,newCallMessage(_));
    EXPECT_CALL(timerPortMock,startTimer(_));
    objectUnderTest.handleReceivedCallTalk("to jest test");
}

TEST_F(ApplicationTalkingTestSuite,shallhandleReceivedCallRejectOnTalkingState)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,showConnected());
    objectUnderTest.handleReceivedCallReject(PHONE_NUMBER);

}

TEST_F(ApplicationTalkingTestSuite,shallhandleUnknownRecipientOnTalkingState)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,showConnected());
    objectUnderTest.handleUnknownRecipient();
}

TEST_F(ApplicationTalkingTestSuite,shallhandleCallRequestOnTalkingState)
{
    EXPECT_CALL(btsPortMock,sendCallDropped(_));
    objectUnderTest.handleCallRequest(PHONE_NUMBER);
}
TEST_F(ApplicationTalkingTestSuite,shallHandleTimeoutOnTalkingState)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,showConnected());
    EXPECT_CALL(userPortMock,alertUser(_));
    objectUnderTest.handleTimeout();
}

}
