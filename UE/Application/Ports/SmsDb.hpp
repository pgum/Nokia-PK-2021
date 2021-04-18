#pragma once
#include "ISmsDb.hpp"
#include "SMS.hpp"

namespace ue {

    class SmsDb: public ISmsDb
    {
        private:
            std::vector<SMS> smsList;

        public:
            SmsDb();
            std::vector<SMS> getAllSms() override;
            void addSMS(SMS sms) override;
            SMS getSMS(int smsIndex) override;
    };


}


