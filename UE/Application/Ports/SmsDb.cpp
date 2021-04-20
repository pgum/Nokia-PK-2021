#include "SmsDb.hpp"

namespace ue
{

    SmsDb::SmsDb(){}

    std::vector<SMS> SmsDb::getAllSms(){
        return this->smsList;
    }

    void SmsDb::addSMS(SMS sms){
        this->smsList.push_back(sms);
    }

    SMS* SmsDb::getSMS(int smsIndex){
        return &this->smsList.at(smsIndex);
    }

    /*
    void SmsDb::deleteReadSMS(int smsIndex){
        this->smsList.erase(smsList.begin()+smsIndex);
    }
    */
    bool SmsDb::checkIfAllRead(){
        for(auto it:this->smsList){
            if(it.getRead()==false)return false;
        }
        return true;
    }
}

