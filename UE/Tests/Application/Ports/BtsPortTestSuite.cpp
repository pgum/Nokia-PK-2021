#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/BtsPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/ITransportMock.hpp"
#include "Messages/OutgoingMessage.hpp"
#include "Messages/IncomingMessage.hpp"

namespace ue
{
using namespace ::testing;

class BtsPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::BtsId BTS_ID{13121981ll};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsEventsHandlerMock> handlerMock;
    StrictMock<common::ITransportMock> transportMock;
    common::ITransport::MessageCallback messageCallback;
    common::ITransport::DisconnectedCallback disconnectCallback;

    BtsPort objectUnderTest{loggerMock, transportMock, PHONE_NUMBER};

    BtsPortTestSuite()
    {
        EXPECT_CALL(transportMock, registerMessageCallback(_))
                .WillOnce(SaveArg<0>(&messageCallback));
        EXPECT_CALL(transportMock, registerDisconnectedCallback(_))
                .WillOnce(SaveArg<0>(&disconnectCallback));
        objectUnderTest.start(handlerMock);
    }
    ~BtsPortTestSuite()
    {

        EXPECT_CALL(transportMock, registerMessageCallback(IsNull()));
        EXPECT_CALL(transportMock, registerDisconnectedCallback(IsNull()));
        objectUnderTest.stop();
    }
};

TEST_F(BtsPortTestSuite, shallRegisterHandlersBetweenStartStop)
{
}

TEST_F(BtsPortTestSuite, shallIgnoreWrongMessage)
{
    common::OutgoingMessage wrongMsg{};
    wrongMsg.writeBtsId(BTS_ID);
    messageCallback(wrongMsg.getMessage());
}

TEST_F(BtsPortTestSuite, shallHandleDisconnected)
{
    EXPECT_CALL(handlerMock, handleDisconnected());
    disconnectCallback();
}

TEST_F(BtsPortTestSuite, shallHandleSib)
{
    EXPECT_CALL(handlerMock, handleSib(BTS_ID));
    common::OutgoingMessage msg{common::MessageId::Sib,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    msg.writeBtsId(BTS_ID);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite, shallHandleAttachAccept)
{
    EXPECT_CALL(handlerMock, handleAttachAccept());
    common::OutgoingMessage msg{common::MessageId::AttachResponse,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    msg.writeNumber(true);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite, shallHandleAttachReject)
{
    EXPECT_CALL(handlerMock, handleAttachReject());
    common::OutgoingMessage msg{common::MessageId::AttachResponse,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    msg.writeNumber(false);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallHandleUnknownRecipient)
{
    EXPECT_CALL(handlerMock,handleUnknownRecipient());
    common::OutgoingMessage msg{common::MessageId::UnknownRecipient,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    common::MessageHeader msgHeader{common::MessageId::CallRequest,common::PhoneNumber{},PHONE_NUMBER};
    msg.writeMessageHeader(msgHeader);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallHandleUnknownRecipientSMS)
{
    EXPECT_CALL(handlerMock,handleUnknownRecipientSMS());
    common::OutgoingMessage msg{common::MessageId::UnknownRecipient,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    common::MessageHeader msgHeader{common::MessageId::Sms,common::PhoneNumber{},PHONE_NUMBER};
    msg.writeMessageHeader(msgHeader);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallHandleRecivedCallRequest)
{
    EXPECT_CALL(handlerMock,handleCallRequest(_));
    common::OutgoingMessage msg{common::MessageId::CallRequest,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallHandleRecivedCallAccepted)
{
    EXPECT_CALL(handlerMock,handleReceivedCallAccept(_));
    common::OutgoingMessage msg{common::MessageId::CallAccepted,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallHandleRecivedCallDropped)
{
    EXPECT_CALL(handlerMock,handleReceivedCallTalk(_));
    common::OutgoingMessage msg{common::MessageId::CallTalk,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallHandleRecivedCallTalk)
{
    EXPECT_CALL(handlerMock,handleReceivedCallTalk(_));
    common::OutgoingMessage msg{common::MessageId::CallTalk,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite, shallSendAttachRequest)
{
    common::BinaryMessage msg;
    EXPECT_CALL(transportMock, sendMessage(_)).WillOnce([&msg](auto param) { msg = std::move(param); return true; });
    objectUnderTest.sendAttachRequest(BTS_ID);
    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::AttachRequest, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{}, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(BTS_ID, reader.readBtsId()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}

TEST_F(BtsPortTestSuite,shallHandleSms)
{
    EXPECT_CALL(handlerMock,handleNewSms(_));

    common::OutgoingMessage msg{common::MessageId::Sms,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite,shallSendSms)
{
    common::BinaryMessage msg;
    SMS testSMS;

    testSMS.from = PHONE_NUMBER;
    testSMS.to = common::PhoneNumber{20};
    testSMS.message = "testString";

    EXPECT_CALL(transportMock,sendMessage(_)).WillOnce([&msg](auto param){msg = std::move(param);return true;});

    objectUnderTest.sendSms(testSMS);

    common::IncomingMessage reader(msg);

    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::Sms, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{20}, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ("testString", reader.readRemainingText()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}

TEST_F(BtsPortTestSuite,shallSendCallRequest)
{
    common::BinaryMessage msg;
    auto reciver=common::PhoneNumber{123};

    EXPECT_CALL(transportMock,sendMessage(_)).WillOnce([&msg](auto param){msg = std::move(param);return true;});
    objectUnderTest.sendCallRequest(reciver);

    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallRequest, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{123}, reader.readPhoneNumber()));
}


TEST_F(BtsPortTestSuite,shallSendCallAccept)
{
    common::BinaryMessage msg;
    auto receiver=common::PhoneNumber{123};

    EXPECT_CALL(transportMock,sendMessage(_)).WillOnce([&msg](auto param){msg = std::move(param);return true;});
    objectUnderTest.sendCallAccept(receiver);

    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallAccepted, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{123}, reader.readPhoneNumber()));
}

TEST_F(BtsPortTestSuite,shallSendCallDropped)
{
    common::BinaryMessage msg;
    auto receiver=common::PhoneNumber{123};
    EXPECT_CALL(transportMock,sendMessage(_)).WillOnce([&msg](auto param){msg = std::move(param);return true;});
    objectUnderTest.sendCallDropped(receiver);

    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallDropped, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{123}, reader.readPhoneNumber()));
}

TEST_F(BtsPortTestSuite,shallSendCallTalk)
{
    common::BinaryMessage msg;
    auto receiver=common::PhoneNumber{123};
    std::string msgtext="Wysłałem wiadomość";

    EXPECT_CALL(transportMock,sendMessage(_)).WillOnce([&msg](auto param){msg = std::move(param);return true;});
    objectUnderTest.sendCallTalk(receiver,msgtext);
    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallTalk, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{123}, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(msgtext,reader.readRemainingText()));

}

}
