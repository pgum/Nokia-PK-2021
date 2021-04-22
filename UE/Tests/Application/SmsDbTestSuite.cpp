#include <gtest/gtest.h>

#include "Messages/PhoneNumber.hpp"
#include "Sms.hpp"
#include "SmsDb.hpp"

namespace ue
{
using namespace ::testing;

class SmsDbTestSuite : public Test
{
protected:
    static constexpr common::PhoneNumber phoneNumber{112};

    SmsDb objectUnderTest;
};

TEST_F(SmsDbTestSuite, shallAddReceivedSms)
{
    const Sms sms{phoneNumber, "example text"};
    objectUnderTest.addReceivedSms(sms);

    const auto& messages = objectUnderTest.getSmsMessages();
    auto [_, smsState] = messages[0];
    ASSERT_EQ(smsState, SmsState::NotViewed);
}

//todo add test getMesagesTest

//todo add test getSms

//todo add test updateSmsState

}  // namespace ue