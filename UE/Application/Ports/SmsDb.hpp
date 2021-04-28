#pragma once
#include "ISmsDb.hpp"
#include "SMS.hpp"

namespace ue {

    class SmsDb: public ISmsDb
    {
        private:
            std::vector<SMS> receivedSMS;
            std::vector<SMS> sendSMS;

        public:
            SmsDb();
            std::vector<SMS> getAllReceivedSms() override;
            SMS getReceivedSms(int smsIndex) override;
            void addReceivedSms(SMS sms) override;

            void addSendSms(SMS sms) override;

            void unknownRecipientSms() override;
    };


}


