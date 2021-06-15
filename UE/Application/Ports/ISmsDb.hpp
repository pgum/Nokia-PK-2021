#pragma once
#include <vector>
#include <memory>
#include "SMS.hpp"

namespace ue
{
    class ISmsDb{
    public:
        virtual ~ISmsDb() = default;
        virtual std::unique_ptr<std::vector<SMS>> getAllReceivedSms() = 0;
        virtual void addSendSms(SMS sms) = 0;
        virtual void addReceivedSms(SMS sms) = 0;
        virtual SMS getReceivedSms(int smsIndex) = 0;
        virtual void unknownRecipientSms() = 0;
    };
}


