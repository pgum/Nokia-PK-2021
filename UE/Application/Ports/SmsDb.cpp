#include "SmsDb.hpp"

namespace ue
{

    SmsDb::SmsDb(){}

    std::unique_ptr<std::vector<SMS>> SmsDb::getAllReceivedSms(){
        return std::make_unique<std::vector<SMS>>(this->receivedSMS);
    }

    void SmsDb::addSendSms(SMS sms){
        this->sendSMS.push_back(sms);
    }

    void SmsDb::addReceivedSms(SMS sms){
        this->receivedSMS.push_back(sms);
    }

    SMS SmsDb::getReceivedSms(int smsIndex){
        return *this->receivedSMS.at(smsIndex).setRead(smsRead::Read);
    }

    void SmsDb::unknownRecipientSms(){
        this->sendSMS.back().setReceived(smsReceived::NotReceived);
    }

}

