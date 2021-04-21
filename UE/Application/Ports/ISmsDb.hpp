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
        virtual void addSendSMS(SMS sms) = 0;
        virtual void addReceivedSMS(SMS sms) = 0;
        virtual SMS getReceivedSMS(int smsIndex) = 0;
        virtual void unknownRecipientSMS(int smsIndex) = 0;
        //virtual void deleteReadSMS(int smsIndex) = 0;
        virtual bool checkIfAllReceivedRead() = 0;
    };
}


