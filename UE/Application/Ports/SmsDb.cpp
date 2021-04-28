#include "SmsDb.hpp"

namespace ue
{

    SmsDb::SmsDb(){}

    std::vector<SMS> SmsDb::getAllReceivedSms(){
        return this->receivedSMS;
    }

    void SmsDb::addSendSMS(SMS sms){
        this->sendSMS.push_back(sms);
    }

    void SmsDb::addReceivedSMS(SMS sms){
        this->receivedSMS.push_back(sms);
    }

    SMS SmsDb::getReceivedSMS(int smsIndex){
        return this->receivedSMS.at(smsIndex).setRead();
    }

    void SmsDb::unknownRecipientSMS(){
        int vectorSize = this->receivedSMS.size();
        int lastSmsIndex = vectorSize -1;
        return this->sendSMS.at(lastSmsIndex).setNotReceived();
    }

    /*
    void SmsDb::deleteReadSMS(int smsIndex){
        this->smsList.erase(smsList.begin()+smsIndex);
    }
    */
    bool SmsDb::checkIfAllReceivedRead(){
        for(auto it:this->receivedSMS){
            if(it.getRead()==false)return false;
        }
        return true;
    }
}

