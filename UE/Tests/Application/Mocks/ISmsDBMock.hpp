#pragma once
#include "Ports/ISmsDb.hpp"
#include "Ports/SMS.hpp"
#include <gmock/gmock.h>

namespace ue{
    class ISmsDBMock: public ISmsDb
    {
        public:
            ISmsDBMock();
            /*virtual std::vector<SMS> getAllSms() = 0;
            virtual void addSMS(SMS sms) = 0;*/
            MOCK_METHOD(std::vector<SMS>,getAllSms,(),(final));
            MOCK_METHOD(void,addSMS,(SMS sms),(final));
    };
}


