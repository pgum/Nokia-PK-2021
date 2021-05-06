#include "SmsDb.hpp"

namespace ue
{

    SmsDb::SmsDb(){}

    std::vector<SMS> SmsDb::getAllReceivedSms(){
        return this->receivedSMS;
    }

    void SmsDb::addSendSms(SMS sms){
        this->sendSMS.push_back(sms);
    }

    void SmsDb::addReceivedSms(SMS sms){
        this->receivedSMS.push_back(sms);
    }

    SMS SmsDb::getReceivedSms(int smsIndex){
        return *this->receivedSMS.at(smsIndex).setRead(true);
    }

    void SmsDb::unknownRecipientSms(){
        int vectorSize = this->receivedSMS.size();
        int lastSmsIndex = vectorSize -1;
        this->sendSMS.at(lastSmsIndex).setReceived(false);
    }

}

