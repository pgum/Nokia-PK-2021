#pragma once
#include <vector>
#include "SMS.hpp"

namespace ue
{
    class ISmsDb{

    public:
        virtual ~ISmsDb() = default;
        virtual std::vector<SMS> getAllSms() = 0;
        virtual void addSMS(SMS sms) = 0;
    };
}


