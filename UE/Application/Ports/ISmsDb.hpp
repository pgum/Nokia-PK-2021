#pragma once
#include <vector>
#include "SMS.hpp"

namespace ue
{
    class ISmsDb{
    private:
        std::vector<SMS> smsList;
    public:
        virtual ~ISmsDb() = default;
        virtual std::vector<SMS> getAllReceivedSms() = 0;
        virtual void addSendSms(SMS sms) = 0;
        virtual void addReceivedSms(SMS sms) = 0;
        virtual SMS getReceivedSms(int smsIndex) = 0;
        virtual void unknownRecipientSms() = 0;
    };
}


