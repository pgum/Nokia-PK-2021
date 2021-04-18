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
        virtual std::vector<SMS> getAllSms() = 0;
        virtual void addSMS(SMS sms) = 0;
        virtual SMS getSMS(int smsIndex) = 0;
    };
}


