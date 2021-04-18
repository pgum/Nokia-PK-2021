#include "SmsDb.hpp"

namespace ue
{


    std::vector<SMS> SmsDb::getAllSms(){
        return this->smsList;
    }

    void SmsDb::addSMS(SMS sms){
        this->smsList.push_back(sms);
    }

}

