#pragma once
#include "Ports/ISmsDb.hpp"
#include "Ports/SMS.hpp"
#include <gmock/gmock.h>

namespace ue{
    class ISmsDBMock: public ISmsDb
    {
        public:
            ISmsDBMock();
            MOCK_METHOD(SMS,getReceivedSMS,(int smsIndex),(final));
            MOCK_METHOD(std::vector<SMS>,getAllReceivedSms,(),(final));
            MOCK_METHOD(void,addSendSMS,(SMS sms),(final));
            MOCK_METHOD(void,addReceivedSMS,(SMS sms),(final));
            MOCK_METHOD(bool,checkIfAllReceivedRead,(),(final));
            MOCK_METHOD(void,unknownRecipientSMS,(),(final));
    };
}


