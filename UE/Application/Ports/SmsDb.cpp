#include "SmsDb.hpp"

namespace ue
{
    SmsDb::SmsDb(){
        common::PhoneNumber phone1,phone2;
        phone1.value=1;
        phone2.value=2;
        SMS testSms1("hello world",phone1,false);
        SMS testSms2("hello world 2",phone2,false);
        this->smsList.push_back(testSms1);
        this->smsList.push_back(testSms2);
    }

    std::vector<SMS> SmsDb::getAllSms(){
        return this->smsList;
    }

    void SmsDb::addSMS(SMS sms){
        this->smsList.push_back(sms);
    }

    SMS SmsDb::getSMS(int smsIndex){
        return this->smsList.at(smsIndex);
    }

}

