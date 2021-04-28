#pragma once
#include "Ports/ISmsDb.hpp"
#include "Ports/SMS.hpp"
#include <gmock/gmock.h>

namespace ue{
    class ISmsDBMock: public ISmsDb
    {
        public:
            ISmsDBMock();
            MOCK_METHOD(SMS,getReceivedSms,(int smsIndex),(final));
            MOCK_METHOD(std::vector<SMS>,getAllReceivedSms,(),(final));
            MOCK_METHOD(void,addSendSms,(SMS sms),(final));
            MOCK_METHOD(void,addReceivedSms,(SMS sms),(final));
            MOCK_METHOD(void,unknownRecipientSms,(),(final));
    };
}


