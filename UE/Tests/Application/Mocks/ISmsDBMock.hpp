#pragma once
#include "Ports/ISmsDb.hpp"
#include "Ports/SMS.hpp"
#include <gmock/gmock.h>

namespace ue{
    class ISmsDBMock: public ISmsDb
    {
        public:
            ISmsDBMock();
            MOCK_METHOD(SMS,getSMS,(int smsIndex),(final));
            MOCK_METHOD(std::vector<SMS>,getAllSms,(),(final));
            MOCK_METHOD(void,addSMS,(SMS sms),(final));
    };
}


