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
            void addSendSMS(SMS sms) override;
            void addReceivedSMS(SMS sms) override;
            SMS getReceivedSMS(int smsIndex) override;
            void unknownRecipientSMS(int smsIndex) override;
            bool checkIfAllReceivedRead() override;
            //void deleteReadSMS(int smsIndex) override;
    };


}


